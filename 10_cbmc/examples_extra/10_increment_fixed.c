#include <pthread.h>

int x;
pthread_mutex_t m;

void *inc_x(void *void_ptr) {
    pthread_mutex_lock(&m);
    int t = x;
    x = t + 1;
    pthread_mutex_unlock(&m);

    pthread_exit(NULL);
    return NULL;
}

int main() {
    pthread_t inc_x_thread;
    pthread_mutex_init(&m, NULL);

    x = 0;

    /* create a second thread which executes inc_x(&x) */
    if (pthread_create(&inc_x_thread, NULL, &inc_x, NULL)) {
        // error creating thread
        return 1;
    }
    pthread_mutex_lock(&m);
    int s = x;
    x = s + 1;
    pthread_mutex_unlock(&m);

    /* wait for the second thread to finish */
    if (pthread_join(inc_x_thread, NULL)) {
        // error joining thread
        return 2;
    }

    __CPROVER_assert(x == 2, "");

    pthread_exit(NULL);
    return 0;
}
