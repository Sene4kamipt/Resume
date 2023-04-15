#include <fcntl.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <unistd.h>

typedef struct Item {
  struct Item *next;
  int64_t value;
} item_t;

typedef struct {
  int64_t number_of_thread;
  int64_t amount_of_numbers;
} arguments;

item_t* starting_point = NULL;
item_t* finish = NULL;

void* make_arr(void* argum) {
  int64_t curr_number = (((arguments*)argum)->number_of_thread) * (((arguments*)argum)->amount_of_numbers);
  while (!finish &&curr_number != 0 ) {
    sched_yield();
  }
  while (finish!=0 &&finish->value + 1 != curr_number) {
    sched_yield();
  }
  while (curr_number < ((((arguments*)argum)->number_of_thread) + 1)* (((arguments*)argum)->amount_of_numbers)) {
    item_t *input_elem = malloc(16);
    if (!starting_point) {
      starting_point = input_elem;
      starting_point->value = curr_number;
      starting_point->next = NULL;
    }
    input_elem->next = NULL;
    input_elem->value = curr_number;
    item_t* last_finish = atomic_exchange(&finish, input_elem);
    if (last_finish!=0) {
      last_finish->next = input_elem;
      curr_number++;
    }
    else{
      curr_number++;
    }
  }
}

int main(int argc, char* argv[]) {
  pthread_t threads[atoll(argv[1])];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, 8192);
  arguments argum[atoll(argv[1])];
  for(int64_t i = 0; i < atoll(argv[1]); i++) {
    argum[i].number_of_thread = i;
    argum[i].amount_of_numbers = atoll(argv[2]);
    pthread_create(&threads[i], &attr, &make_arr, (void*)&(argum[i]));
  }
  int count = 0;
  while(count < atoll(argv[1])) {
    pthread_join(threads[count], NULL);
    ++count;
  }
  while (starting_point) {
    int64_t outpu = starting_point->value;
    printf("%ld ", outpu);
    starting_point = starting_point->next;
  }
}
