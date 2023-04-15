#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
typedef struct {
  uint64_t r_border;
  uint64_t last_sp;
  int number;
} arguments;

void* make_prime(void* argum) {
  uint64_t ans = 0;
  uint64_t i = (((arguments*)argum) -> r_border); 
  while (true){
    int flag = 0;
    for (uint64_t j = 2; j<=i;++j){
      if (j>=i){
	flag =1;
	break;
      }
      if(i%j==0){
	break;
      }
    }
    if (flag){
      write((((arguments*)argum) -> last_sp), &i, sizeof(i));
      ans++;
    }
    ++i;
    if (ans == (((arguments*)argum) -> number)){break;}
  }
  return 0;
}

int main(int argc, char* argv[]) {
  int sp[2];
  socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
  arguments argum;
  argum.r_border = atoll(argv[1]);
  argum.last_sp = sp[1];
  argum.number = atoi(argv[3]);
  pthread_t th;
  pthread_create(&th, NULL, make_prime, (void*)&argum);
  uint64_t outpu;
  for (int i=0; i<argum.number; ++i){
    read(sp[0], &outpu, sizeof(outpu));
    printf("%ld ",outpu);
  }
  return 0;
}

