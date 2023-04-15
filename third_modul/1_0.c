#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


static void* thread_func(void* arg) {
    int val;
    if (scanf("%d ", &val) != 1) {
        return NULL;
    }
    pthread_t nexr_thread;
    pthread_create(&nexr_thread, NULL, thread_func, 0);
    pthread_join(nexr_thread, NULL);
    printf("%d ", val);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL,thread_func, 0);
    pthread_join(thread,NULL);
    return 0;
}
