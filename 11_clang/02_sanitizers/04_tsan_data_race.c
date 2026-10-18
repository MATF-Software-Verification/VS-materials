#include <pthread.h>
#include <stdio.h>

enum { ITERATIONS = 100000 };

static int counter = 0;

static void *worker(void *arg) {
    (void)arg;

    for (int i = 0; i < ITERATIONS; i++) {
        counter++;
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
