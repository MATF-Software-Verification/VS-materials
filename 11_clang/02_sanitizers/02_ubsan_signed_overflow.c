#include <limits.h>
#include <stdio.h>

static int bonus_points(int solved_tasks) { return solved_tasks * 1000000; }

int main(void) {
    int solved_tasks = INT_MAX / 1000000 + 1;
    printf("bonus=%d\n", bonus_points(solved_tasks));
    return 0;
}
