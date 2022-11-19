// main.cpp
#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
static int resource1;

pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
static int resource2;

static int LOOPS = 1000;

void *run1(void *args) {
    for (int i = 1; i < LOOPS; ++i) {
        pthread_mutex_lock(&m1);
        usleep(10);
        pthread_mutex_lock(&m2);
        if (resource1 % 3)
            ++resource2;
        usleep(10);
        pthread_mutex_unlock(&m2);
        pthread_mutex_unlock(&m1);
    }
    return NULL;
}

void *run2(void *args) {
    for (int i = 1; i < LOOPS; ++i) {
        pthread_mutex_lock(&m1);
        usleep(10);
        pthread_mutex_lock(&m2);
        if (resource2 % 2 == 0)
            ++resource1;
        usleep(10);
        pthread_mutex_unlock(&m1);
        pthread_mutex_unlock(&m2);
    }
    return NULL;
}

int main() {
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, run1, NULL);
    usleep(5);
    pthread_create(&t2, NULL, run2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
