#include <pthread.h>

int x = 0, y = 0;

/* this function is run by the second thread */
void inc_x(void *void_ptr) {
    /* increment x to 10 */
    for (int i = 0; i < 10; ++i)
        x++;

    pthread_exit(NULL);
    return NULL;
}

int main() {
    /* this variable is our reference to the second thread */
    pthread_t inc_x_thread;

    /* create a second thread which executes inc_x() */
    if (pthread_create(&inc_x_thread, NULL, &inc_x, NULL)) {
        // error creating thread
        return 1;
    }

    /* increment y to 10 in the first thread */
    for (int j = 0; j < 10; ++j)
        y++;

    /* wait for the second thread to finish */
    if (pthread_join(inc_x_thread, NULL)) {
        // error joining thread
        return 2;
    }

    /* show the results - x is now 10 thanks to the second thread */
    __CPROVER_assert(x == y && x == 10, "");

    pthread_exit(NULL);
    return 0;
}
