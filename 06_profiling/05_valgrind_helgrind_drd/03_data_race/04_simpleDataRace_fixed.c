#include <pthread.h>
#include <stdio.h>

int var = 0;
pthread_mutex_t m;
pthread_cond_t moze;
int SIGNAL_CHILD = 0;

void *child_fn(void *arg) {
    pthread_mutex_lock(&m);

    while (!SIGNAL_CHILD)
        pthread_cond_wait(&moze, &m);

    var = 10; /* Unprotected relative to parent */
    pthread_mutex_unlock(&m);

    return NULL;
}

int main(void) {
    pthread_t child1;

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&moze, NULL);
    pthread_create(&child1, NULL, child_fn, NULL);

    pthread_mutex_lock(&m);

    var = 20; /* Unprotected relative to child */

    pthread_cond_signal(&moze);
    SIGNAL_CHILD = 1;
    pthread_mutex_unlock(&m);

    pthread_join(child1, NULL);

    printf("VAR = %d\n", var);

    return 0;
}
