#include <klee/klee.h>

int main() {
    int k, n = 0;
    int a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
    int a10, a11, a12, a13, a14, a15, a16, a17, a18, a19;
    int a20, a21, a22, a23, a24, a25, a26, a27, a28, a29;
    int a30, a31, a32, a33, a34, a35, a36, a37, a38, a39;
    int a40, a41, a42, a43, a44, a45, a46, a47, a48, a49;

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
    klee_make_symbolic(&a30, sizeof(a30), "a30");
    klee_make_symbolic(&a31, sizeof(a31), "a31");
    klee_make_symbolic(&a32, sizeof(a32), "a32");
    klee_make_symbolic(&a33, sizeof(a33), "a33");
    klee_make_symbolic(&a34, sizeof(a34), "a34");
    klee_make_symbolic(&a35, sizeof(a35), "a35");
    klee_make_symbolic(&a36, sizeof(a36), "a36");
    klee_make_symbolic(&a37, sizeof(a37), "a37");
    klee_make_symbolic(&a38, sizeof(a38), "a38");
    klee_make_symbolic(&a39, sizeof(a39), "a39");
    klee_make_symbolic(&a40, sizeof(a40), "a40");
    klee_make_symbolic(&a41, sizeof(a41), "a41");
    klee_make_symbolic(&a42, sizeof(a42), "a42");
    klee_make_symbolic(&a43, sizeof(a43), "a43");
    klee_make_symbolic(&a44, sizeof(a44), "a44");
    klee_make_symbolic(&a45, sizeof(a45), "a45");
    klee_make_symbolic(&a46, sizeof(a46), "a46");
    klee_make_symbolic(&a47, sizeof(a47), "a47");
    klee_make_symbolic(&a48, sizeof(a48), "a48");
    klee_make_symbolic(&a49, sizeof(a49), "a49");

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
    if (a30 > 0)
        a30 = 1;
    else
        a30 = -1;
    if (a31 > 0)
        a31 = 1;
    else
        a31 = -1;
    if (a32 > 0)
        a32 = 1;
    else
        a32 = -1;
    if (a33 > 0)
        a33 = 1;
    else
        a33 = -1;
    if (a34 > 0)
        a34 = 1;
    else
        a34 = -1;
    if (a35 > 0)
        a35 = 1;
    else
        a35 = -1;
    if (a36 > 0)
        a36 = 1;
    else
        a36 = -1;
    if (a37 > 0)
        a37 = 1;
    else
        a37 = -1;
    if (a38 > 0)
        a38 = 1;
    else
        a38 = -1;
    if (a39 > 0)
        a39 = 1;
    else
        a39 = -1;
    if (a40 > 0)
        a40 = 1;
    else
        a40 = -1;
    if (a41 > 0)
        a41 = 1;
    else
        a41 = -1;
    if (a42 > 0)
        a42 = 1;
    else
        a42 = -1;
    if (a43 > 0)
        a43 = 1;
    else
        a43 = -1;
    if (a44 > 0)
        a44 = 1;
    else
        a44 = -1;
    if (a45 > 0)
        a45 = 1;
    else
        a45 = -1;
    if (a46 > 0)
        a46 = 1;
    else
        a46 = -1;
    if (a47 > 0)
        a47 = 1;
    else
        a47 = -1;
    if (a48 > 0)
        a48 = 1;
    else
        a48 = -1;
    if (a49 > 0)
        a49 = 1;
    else
        a49 = -1;

    n = (a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 +
         a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22 + a23 + a24 +
         a25 + a26 + a27 + a28 + a29 + a30 + a31 + a32 + a33 + a34 + a35 + a36 +
         a37 + a38 + a39 + a40 + a41 + a42 + a43 + a44 + a45 + a46 + a47 + a48 +
         a49);

    k = k / (n + 50);
}
