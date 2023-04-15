#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <limits.h>

static void* func (void* sum_thread){
    int input = 0;
    scanf("%d", &input);
    *((int*)sum_thread)+=input;
    if (*((int*)sum_thread+1) == 1){
        while (scanf("%d", &input)==1){
            *((int*)sum_thread)+=input;
        }
    }
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setguardsize(&attr, 0);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN/4);
    *((int*)sum_thread+1) -=1;
    pthread_create(&thread, &attr, func, sum_thread);
    pthread_join(thread, NULL);
    return NULL;
}

int main(int argc, char* argv[]){
    int number_threads = atoi(argv[1]);
    int sum_thread[2] = {0, number_threads};
    if (number_threads<2){
        return 0;
    }
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setguardsize(&attr, 0);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN/4);
    pthread_create(&thread, &attr, func, sum_thread);
    pthread_join(thread, NULL);
    printf("%d", sum_thread[0]);
    return 0;
}

