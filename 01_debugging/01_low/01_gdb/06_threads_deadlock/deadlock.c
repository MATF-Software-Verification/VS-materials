#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_mutex_t left = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t right = PTHREAD_MUTEX_INITIALIZER;

static void *worker_a(void *arg) {
    (void)arg;
    pthread_mutex_lock(&left);
    sleep(1);
    pthread_mutex_lock(&right);
    puts("worker_a entered critical section");
    pthread_mutex_unlock(&right);
    pthread_mutex_unlock(&left);
    return NULL;
}

static void *worker_b(void *arg) {
    (void)arg;
    pthread_mutex_lock(&right);
    sleep(1);
    pthread_mutex_lock(&left);
    puts("worker_b entered critical section");
    pthread_mutex_unlock(&left);
    pthread_mutex_unlock(&right);
    return NULL;
}

int main(void) {
    pthread_t a;
    pthread_t b;

    pthread_create(&a, NULL, worker_a, NULL);
    pthread_create(&b, NULL, worker_b, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);
    return 0;
}
