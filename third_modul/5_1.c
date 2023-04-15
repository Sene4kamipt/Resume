#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
 
volatile sig_atomic_t sigterm_sigint_flag = 0;
 
void sigterm_sigint_handler(int sig)
{
    sigterm_sigint_flag = 1;
}
 
int create_server(const char* server_ip_addr_str, int server_port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == socket_fd) {
        error(EXIT_FAILURE, errno, "Unable to create a new socket");
    }
 
    struct in_addr server_ip_addr;
    if (0 == inet_aton(server_ip_addr_str, &server_ip_addr)) {
        close(socket_fd);
        error(
            EXIT_FAILURE,
            0,
            "Invalid server IP address: %s",
            server_ip_addr_str);
    }
    in_port_t little_endian_server_port = htons(server_port);
 
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_addr = server_ip_addr,
        .sin_port = little_endian_server_port};
 
    int bind_status = bind(
        socket_fd, (const struct sockaddr*)(&server_addr), sizeof(server_addr));
    if (0 != bind_status) {
        close(socket_fd);
        error(
            EXIT_FAILURE,
            errno,
            "Could not bind to %s:%d",
            server_ip_addr_str,
            server_port);
    }
 
    return socket_fd;
}
 
int accept_client(
    int socket_fd,
    const char* server_ip_addr_str,
    int server_port)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_fd =
        accept(socket_fd, (struct sockaddr*)(&client_addr), &addr_len);
    if (-1 == client_fd) {
        close(socket_fd);
        if (errno == EINTR) {
            exit(0);
        }
 
        error(
            EXIT_FAILURE,
            errno,
            "Could not accept client on %s:%d",
            server_ip_addr_str,
            server_port);
    }
 
    return client_fd;
}
 
size_t recv_client_message(
    int client_fd,
    int socket_fd,
    char* buffer,
    size_t buffer_len)
{
    int recv_status = recv(client_fd, buffer, buffer_len, 0);
    if (recv_status < 0) {
        if (errno == EINTR) {
            return recv_client_message(
                client_fd, socket_fd, buffer, buffer_len);
        }
 
        close(client_fd);
        close(socket_fd);
 
        error(EXIT_FAILURE, errno, "Could not receive message from the client");
    } else if (recv_status == 0) {
        close(client_fd);
        close(socket_fd);
        error(EXIT_FAILURE, 0, "Zero length message from the client");
    }
 
    int message_len = recv_status;
    return message_len;
}
 
void send_message_to_client(
    int socket_fd,
    int client_fd,
    const char* message,
    size_t message_len)
{
    if (-1 == send(client_fd, message, message_len, 0)) {
        if (errno == EINTR) {
            send_message_to_client(socket_fd, client_fd, message, message_len);
            return;
        }
 
        close(client_fd);
        close(socket_fd);
 
        error(EXIT_FAILURE, errno, "Could not send message to the client");
    }
}
 
void process_client(
    int socket_fd,
    const char* server_ip_addr_str,
    int server_port,
    char* dir_path)
{
    int client_fd = accept_client(socket_fd, server_ip_addr_str, server_port);
 
    char buffer[16384];
    recv_client_message(client_fd, socket_fd, buffer, sizeof(buffer));
 
    char file_name[1024];
    sscanf(buffer, "GET %s HTTP/1.1\r\n", file_name);
    char abs_file_path[1024];
    strcpy(abs_file_path, dir_path);
    strcat(abs_file_path, file_name);
 
    char response[16384];
    response[0] = '\0';
 
    bool file_exists = access(abs_file_path, F_OK) == 0;
    bool file_is_readable = access(abs_file_path, R_OK) == 0;
    if (!file_exists) {
        strcat(response, "HTTP/1.1 404 Not Found\r\n");
    } else if (!file_is_readable) {
        strcat(response, "HTTP/1.1 403 Forbidden\r\n");
    } else {
        strcat(response, "HTTP/1.1 200 OK\r\n");
    }
 
    size_t content_length;
    if (!file_exists || !file_is_readable) {
        content_length = 0;
    } else {
        struct stat file_stats;
        stat(abs_file_path, &file_stats);
        content_length = file_stats.st_size;
    }
 
    char content_length_response[1024];
    sprintf(content_length_response, "Content-Length: %ld\r\n", content_length);
    strcat(response, content_length_response);
 
    strcat(response, "\r\n");
 
    if (file_exists && file_is_readable) {
        int fd = open(abs_file_path, O_RDONLY);
        char* file_contents =
            (char*)mmap(0, content_length, PROT_READ, MAP_PRIVATE, fd, 0);
        strncat(response, file_contents, content_length);
        munmap(file_contents, content_length);
    }
 
    send_message_to_client(socket_fd, client_fd, response, strlen(response));
 
    close(client_fd);
}
 
int main(int argc, char* argv[])
{
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGINT);
    sigdelset(&mask, SIGTERM);
    sigprocmask(SIG_SETMASK, &mask, NULL);
 
    struct sigaction sigterm_sigint_action = {
        .sa_handler = sigterm_sigint_handler};
    sigaction(SIGTERM, &sigterm_sigint_action, NULL);
    sigaction(SIGINT, &sigterm_sigint_action, NULL);
 
    char server_ip_addr_str[1024];
    strcpy(
        server_ip_addr_str,
        inet_ntoa(
            *((struct in_addr**)gethostbyname("localhost")->h_addr_list)[0]));
 
    int server_port = atoi(argv[1]);
    const char* initial_dir_path = argv[2];
    char dir_path[1024];
    strcpy(dir_path, initial_dir_path);
    if (dir_path[strlen(dir_path) - 1] != '/') {
        strcat(dir_path, "/");
    }
 
    int socket_fd = create_server(server_ip_addr_str, server_port);
    if (-1 == listen(socket_fd, SOMAXCONN)) {
        close(socket_fd);
        error(
            EXIT_FAILURE,
            errno,
            "Could not start to listen on %s:%d",
            server_ip_addr_str,
            server_port);
    }
 
    while (sigterm_sigint_flag != 1) {
        process_client(socket_fd, server_ip_addr_str, server_port, dir_path);
    }
 
    close(socket_fd);
}
