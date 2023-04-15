#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct ThreadData {
    double* l;
    double* v;
    double* r;
    int n;
    pthread_mutex_t* guard;
};

void* worker(void* arg_)
{
    struct ThreadData arg = *(struct ThreadData*)arg_;
    for (int i = 0; i < arg.n; ++i) {
        pthread_mutex_lock(arg.guard);
        *arg.l += 0.99;
        *arg.v += 1;
        *arg.r += 1.01;
        pthread_mutex_unlock(arg.guard);
    }
}

int main(int argc, char* argv[])
{
    pthread_mutex_t guard;
    int n;
    n = atoi(argv[1]);
    int k = atoi(argv[2]);
    pthread_mutex_init(&guard, NULL);
    double values[k];
    struct ThreadData threadDatas[k];
    pthread_t threads[k];
    for (int i = 0; i < k; ++i) {
        threadDatas[i].l = &(values[(i + k - 1) % k]);
        threadDatas[i].v = &(values[i]);
        threadDatas[i].r = &(values[(i + 1) % k]);
        threadDatas[i].n = n;
        threadDatas[i].guard = &guard;
        pthread_create(&threads[i], NULL, worker, &threadDatas[i]);
    }
    for (int i = 0; i < k; ++i) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < k; ++i) {
        printf("%.10g\n", values[i]);
    }
}
