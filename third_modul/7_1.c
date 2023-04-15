#include<arpa/inet.h>
#include<ctype.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>

volatile sig_atomic_t signal_term = 1;

void term_handler(int sig) {
  signal_term = 0;
}

int main(int argc, char* argv[]) {

  struct sigaction term_func = {
    .sa_handler = term_handler,
    .sa_flags = SA_RESTART
  };
  
  sigaction(SIGTERM, &term_func, NULL);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in addr = {
    .sin_addr = inet_addr("127.0.0.1"),
    .sin_family = AF_INET,
    .sin_port = htons(atoi(argv[1]))
  };

  bind(sock, (struct sockaddr*) &addr, sizeof(addr));
  listen(sock, 128);

  int epoll = epoll_create(1);
  struct epoll_event epoll_fds[4096];
  
  int flags = fcntl(sock, F_GETFD);
  fcntl(sock, F_SETFL, flags | O_NONBLOCK);
  struct epoll_event sock_event = {
    .events = EPOLLIN,
    .data.fd = sock
  };
  epoll_ctl(epoll, EPOLL_CTL_ADD, sock, &sock_event);

  while (signal_term) {
    int number_got = epoll_wait(epoll, epoll_fds, sizeof(epoll_fds), -1);
    for (int i = 0; i < number_got; ++i) {
      if (epoll_fds[i].data.fd != sock) {
        int text_size;
        char text_buffer[4096];
        while ((text_size = read(epoll_fds[i].data.fd, text_buffer, sizeof(text_buffer))) > 0) {
          for (int j = 0; j < text_size; ++j) {
            text_buffer[j] = toupper(text_buffer[j]);
          }
        write(epoll_fds[i].data.fd, text_buffer, text_size);
        }
      } 
      else {
        socklen_t sz = sizeof(addr);
        int fd_cp = accept(sock, (struct sockaddr*) &addr, &sz);
        if (fd_cp != -1){
          flags = fcntl(fd_cp, F_GETFD);
  	  fcntl(fd_cp, F_SETFL, flags | O_NONBLOCK);
  	  struct epoll_event curr_epol_fd = {
    	    .events = EPOLLIN,
    	    .data.fd = fd_cp
  	  };
  	  epoll_ctl(epoll, EPOLL_CTL_ADD, fd_cp, &curr_epol_fd);
        }   
      }
    }
  }
  close(sock);
  return 0;
}
