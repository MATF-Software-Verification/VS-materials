#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

static bool bonus_points(int solved_tasks, int *result) {
    if (solved_tasks < 0 || solved_tasks > INT_MAX / 1000000) {
        return false;
    }

    *result = solved_tasks * 1000000;
    return true;
}

int main(void) {
    int solved_tasks = INT_MAX / 1000000 + 1;
    int result = 0;

    if (!bonus_points(solved_tasks, &result)) {
        puts("broj zadataka je van opsega");
        return 0;
    }

    printf("bonus=%d\n", result);
    return 0;
}
