#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<sys/types.h>

volatile sig_atomic_t exit_flag = 0;

void alarm_handler(int signum){
  exit_flag = 1;
}

static uint16_t control_sum(void* addr, int len)
{
  uint32_t answer = 0;
  uint16_t *addr_cp = addr;

  while (len >= 2) {
    len -= 2;
    answer += *addr_cp++;
  }

  if (len != 0) {
    answer += *(unsigned char *)addr_cp;
  }

  while(answer>>16){
    answer = (answer >> 16) + (answer & 0xFFFF);
  }
  return ~answer;
}

int ping(char* ip){
  struct sockaddr_in addr = {
    .sin_addr = inet_addr(ip),
    .sin_family = AF_INET
  };
  
  socklen_t len = sizeof(addr);

  struct icmphdr send = {
    .checksum = 0
  };
    
  send.type = ICMP_ECHO;
  send.code = 0;
  socklen_t len_send = sizeof(send);
  send.checksum = control_sum(&send, len_send);
  
  int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

  if(sendto(sock, &send, len_send, 0, (struct sockaddr*) &addr, len) <= 0){
    close(sock);
    return 0;
  }

  struct icmphdr get;
  
  len_send = sizeof(get);
  len = sizeof(addr);

  if(recvfrom(sock, &get, len_send, 0, (struct sockaddr*) &addr, &len) <= 0){
    close(sock);
    return 0;
  }

  close(sock);
  return 1;
}

int main(int argc, char* argv[]){
  int answer;

  struct sigaction alarm_func = {
    .sa_mask = 0,
    .sa_handler = alarm_handler,
    .sa_flags = 0
  };
  
  sigaction(SIGALRM, &alarm_func, NULL);
  
  alarm(atoi(argv[2]));
  while(exit_flag == 0){
    answer += ping((char*)argv[1]);
    usleep(atoi(argv[3]));
  }

  printf("%d", answer);
  return 0;
}
