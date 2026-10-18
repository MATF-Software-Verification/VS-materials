#include <klee/klee.h>

int main() {
    int k, n = 0;
    int a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
    int a10;

    klee_make_symbolic(&a0, sizeof(a0), "a0");
    klee_make_symbolic(&a1, sizeof(a1), "a1");
    klee_make_symbolic(&a2, sizeof(a2), "a2");
    klee_make_symbolic(&a3, sizeof(a3), "a3");
    klee_make_symbolic(&a4, sizeof(a4), "a4");
    klee_make_symbolic(&a5, sizeof(a5), "a5");
    klee_make_symbolic(&a6, sizeof(a6), "a6");
    klee_make_symbolic(&a7, sizeof(a7), "a7");
    klee_make_symbolic(&a8, sizeof(a8), "a8");
    klee_make_symbolic(&a9, sizeof(a9), "a9");
    klee_make_symbolic(&a10, sizeof(a10), "a10");

    if (a0 > 0)
        a0 = 1;
    else
        a0 = -1;
    if (a1 > 0)
        a1 = 1;
    else
        a1 = -1;
    if (a2 > 0)
        a2 = 1;
    else
        a2 = -1;
    if (a3 > 0)
        a3 = 1;
    else
        a3 = -1;
    if (a4 > 0)
        a4 = 1;
    else
        a4 = -1;
    if (a5 > 0)
        a5 = 1;
    else
        a5 = -1;
    if (a6 > 0)
        a6 = 1;
    else
        a6 = -1;
    if (a7 > 0)
        a7 = 1;
    else
        a7 = -1;
    if (a8 > 0)
        a8 = 1;
    else
        a8 = -1;
    if (a9 > 0)
        a9 = 1;
    else
        a9 = -1;
    if (a10 > 0)
        a10 = 1;
    else
        a10 = -1;

    n = (a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10);

    k = k / (n - 11);
}
