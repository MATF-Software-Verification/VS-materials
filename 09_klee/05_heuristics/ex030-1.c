#include <klee/klee.h>

int main() {
    int k, n = 0;
    int a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
    int a10, a11, a12, a13, a14, a15, a16, a17, a18, a19;
    int a20, a21, a22, a23, a24, a25, a26, a27, a28, a29;

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
    klee_make_symbolic(&a11, sizeof(a11), "a11");
    klee_make_symbolic(&a12, sizeof(a12), "a12");
    klee_make_symbolic(&a13, sizeof(a13), "a13");
    klee_make_symbolic(&a14, sizeof(a14), "a14");
    klee_make_symbolic(&a15, sizeof(a15), "a15");
    klee_make_symbolic(&a16, sizeof(a16), "a16");
    klee_make_symbolic(&a17, sizeof(a17), "a17");
    klee_make_symbolic(&a18, sizeof(a18), "a18");
    klee_make_symbolic(&a19, sizeof(a19), "a19");
    klee_make_symbolic(&a20, sizeof(a20), "a20");
    klee_make_symbolic(&a21, sizeof(a21), "a21");
    klee_make_symbolic(&a22, sizeof(a22), "a22");
    klee_make_symbolic(&a23, sizeof(a23), "a23");
    klee_make_symbolic(&a24, sizeof(a24), "a24");
    klee_make_symbolic(&a25, sizeof(a25), "a25");
    klee_make_symbolic(&a26, sizeof(a26), "a26");
    klee_make_symbolic(&a27, sizeof(a27), "a27");
    klee_make_symbolic(&a28, sizeof(a28), "a28");
    klee_make_symbolic(&a29, sizeof(a29), "a29");

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
    if (a11 > 0)
        a11 = 1;
    else
        a11 = -1;
    if (a12 > 0)
        a12 = 1;
    else
        a12 = -1;
    if (a13 > 0)
        a13 = 1;
    else
        a13 = -1;
    if (a14 > 0)
        a14 = 1;
    else
        a14 = -1;
    if (a15 > 0)
        a15 = 1;
    else
        a15 = -1;
    if (a16 > 0)
        a16 = 1;
    else
        a16 = -1;
    if (a17 > 0)
        a17 = 1;
    else
        a17 = -1;
    if (a18 > 0)
        a18 = 1;
    else
        a18 = -1;
    if (a19 > 0)
        a19 = 1;
    else
        a19 = -1;
    if (a20 > 0)
        a20 = 1;
    else
        a20 = -1;
    if (a21 > 0)
        a21 = 1;
    else
        a21 = -1;
    if (a22 > 0)
        a22 = 1;
    else
        a22 = -1;
    if (a23 > 0)
        a23 = 1;
    else
        a23 = -1;
    if (a24 > 0)
        a24 = 1;
    else
        a24 = -1;
    if (a25 > 0)
        a25 = 1;
    else
        a25 = -1;
    if (a26 > 0)
        a26 = 1;
    else
        a26 = -1;
    if (a27 > 0)
        a27 = 1;
    else
        a27 = -1;
    if (a28 > 0)
        a28 = 1;
    else
        a28 = -1;
    if (a29 > 0)
        a29 = 1;
    else
        a29 = -1;

    n = (a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 +
         a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22 + a23 + a24 +
         a25 + a26 + a27 + a28 + a29);

    k = k / (n + 30);
}
