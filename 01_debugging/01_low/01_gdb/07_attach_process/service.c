#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static volatile sig_atomic_t running = 1;
static unsigned long requests = 0;
static unsigned long slow_path = 0;

static void stop(int signal) {
    (void)signal;
    running = 0;
}

static void handle_request(void) {
    requests++;
    if (requests % 10 == 0) {
        slow_path++;
        usleep(250000);
    } else {
        usleep(50000);
    }
}

int main(void) {
    signal(SIGINT, stop);
    signal(SIGTERM, stop);

    printf("pid=%ld\n", (long)getpid());
    fflush(stdout);

    while (running) {
        handle_request();
    }

    printf("requests=%lu slow_path=%lu\n", requests, slow_path);
    return 0;
}
