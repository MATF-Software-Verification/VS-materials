#include <klee/klee.h>

int main() {
    int k, n = 0;
    int a0, a1, a2, a3, a4;

    klee_make_symbolic(&a0, sizeof(a0), "a0");
    klee_make_symbolic(&a1, sizeof(a1), "a1");
    klee_make_symbolic(&a2, sizeof(a2), "a2");
    klee_make_symbolic(&a3, sizeof(a3), "a3");
    klee_make_symbolic(&a4, sizeof(a4), "a4");

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

    n = (a0 + a1 + a2 + a3 + a4);

    k = k / (n + 5);
}
