/* Naive dining philosophers with inconsistent lock acquisition
   ordering. */

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_t phil[5];
static struct {
    pthread_mutex_t m;
    char pad[120 - sizeof(pthread_mutex_t)];
} chop[5];

void *dine(void *arg) {
    int i;
    long n = (long)arg;
    long left = (long)arg;
    long right = (left + 1) % 5;

    for (i = 0; i < 3 /*arbitrary */; i++) {
        printf("Philosopher %ld is thinking\tleft%ld right%ld\n", n, left,
               right);

        pthread_mutex_lock(&chop[left].m);
        printf("Philosopher %ld took left\n", n);

        pthread_mutex_lock(&chop[right].m);
        printf("Philosopher %ld took right\n", n);

        /* eating */
        printf("Philosopher %ld is eating\n", n);
        usleep(15);

        printf("Philosopher %ld finished eating\n", n);

        pthread_mutex_unlock(&chop[right].m);

        pthread_mutex_unlock(&chop[left].m);
    }
    return NULL;
}

int main(void) {
    long i;
    assert(sizeof(pthread_mutex_t) <= 120);

    for (i = 0; i < 5; i++)
        pthread_mutex_init(&chop[i].m, NULL);

    for (i = 0; i < 5; i++)
        pthread_create(&phil[i], NULL, dine, (void *)i);

    sleep(1);

    for (i = 0; i < 5; i++)
        pthread_join(phil[i], NULL);

    for (i = 0; i < 5; i++)
        pthread_mutex_destroy(&chop[i].m);

    return 0;
}
