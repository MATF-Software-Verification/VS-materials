#include <assert.h>
#include <klee/klee.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int v4, v5;

    if (argc == 2) {
        if (42 * (strlen(argv[1]) + 1) != 504)
            goto LABEL_31;
        v5 = 1;
        if (*argv[1] != 80)
            v5 = 0;
        if (2 * argv[1][3] != 200)
            v5 = 0;
        if (*argv[1] + 16 != argv[1][6] - 16)
            v5 = 0;
        v4 = argv[1][5];
        if (v4 != 9 * strlen(argv[1]) - 4)
            v5 = 0;
        if (argv[1][1] != argv[1][7])
            v5 = 0;
        if (argv[1][1] != argv[1][10])
            v5 = 0;
        if (argv[1][1] - 17 != *argv[1])
            v5 = 0;
        if (argv[1][3] != argv[1][9])
            v5 = 0;
        if (argv[1][4] != 105)
            v5 = 0;
        if (argv[1][2] - argv[1][1] != 13)
            v5 = 0;
        if (argv[1][8] - argv[1][7] != 13)
            v5 = 0;
        if (v5) {
            printf("Good good!\n");
            klee_assert(0);
        } else
        LABEL_31:
            printf("Try again...\n");
    } else {
        printf("Usage: %s <pass>\n", *argv);
    }
}
