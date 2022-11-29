#include <klee/klee.h>

int main() {
    int k, n = 0;
    int a0, a1;

    klee_make_symbolic(&a0, sizeof(a0), "a0");
    klee_make_symbolic(&a1, sizeof(a1), "a1");

    if (a0 > 0)
        a0 = 1;
    else
        a0 = -1;
    if (a1 > 0)
        a1 = 1;
    else
        a1 = -1;

    n = (a0 + a1);

    k = k / (n + 3);
}
