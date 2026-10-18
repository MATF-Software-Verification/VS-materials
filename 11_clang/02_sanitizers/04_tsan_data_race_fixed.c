#include <pthread.h>
#include <stdio.h>

enum { ITERATIONS = 100000 };

static int counter = 0;
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *worker(void *arg) {
    (void)arg;

    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);
    }

    return NULL;
}

int main(void) {
    pthread_t first;
    pthread_t second;

    pthread_create(&first, NULL, worker, NULL);
    pthread_create(&second, NULL, worker, NULL);
    pthread_join(first, NULL);
    pthread_join(second, NULL);

    printf("counter=%d\n", counter);
    return 0;
}
