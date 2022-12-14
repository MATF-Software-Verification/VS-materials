/* 1st very simple example to demostrate Cachegrind */
#include <stdio.h>
#define N 1000

double array_sum(double[N][N]);

double array_sum(double a[N][N]) {
    int i, j;
    double s;
    s = 0;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            s += a[i][j];

    return s;
}

int main(int argc, char **argv) {
    double a[N][N];
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = 0.01;
        }
    }

    /* this is just to prevent the compiler
       from optimizing the upper loop away */
    printf("sum = %10.3f\n", array_sum(a));

    return 0;
}
