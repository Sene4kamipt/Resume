#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>
#include<stdbool.h>

void* addition(void* argum){
  int curr_number;
  int end_of_socket = *(int*)argum;
  int fl =1;
  read(end_of_socket, &curr_number, 4);
  while (fl!=0){
    printf("%d ", curr_number+5);
    curr_number = curr_number+5;
    write(end_of_socket, &curr_number, 4);
    read(end_of_socket, &curr_number, 4);
    fl = ((curr_number <= 95) && (curr_number != 0));
    if ((curr_number>95)&&(curr_number<101)){
      printf("%d ", curr_number+5);
      curr_number = curr_number+5;
      write(end_of_socket, &curr_number, 4);
    }
  }
  close(end_of_socket);
}


void* substraction(void* argum){
  int curr_number;
  int end_of_socket = *(int*)argum;
  int fl =1;
  read(end_of_socket, &curr_number, 4);
  while (fl!=0){
    printf("%d ", curr_number-3);
    curr_number = curr_number-3;
    write(end_of_socket, &curr_number, 4);
    read(end_of_socket, &curr_number, 4);
    fl = (curr_number < 101);
    if (curr_number == 3){
      printf("%d ", curr_number-3);
      curr_number = curr_number-3;
      write(end_of_socket, &curr_number, 4);
    }
  }
  close(end_of_socket);
}

int main(int argc, char* argv[]){
  int sp[2];
  socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
  int curr_number = atoi(argv[1]);
  write(sp[1], &curr_number, 4);
  pthread_t sub;
  pthread_create(&sub, NULL, substraction, &sp[0]);
  pthread_t add;
  pthread_create(&add, NULL, addition, &sp[1]);
  pthread_join(sub, NULL);
  pthread_join(add, NULL);
  return 0;
}
