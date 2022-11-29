#include <stdio.h>

int even(int x) {
    if (x % 2 == 0)
        return 1;
    if (x % 2)
        return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    int x;
    scanf("%d", &x);
    printf("%d", even(x));
    return 0;
}