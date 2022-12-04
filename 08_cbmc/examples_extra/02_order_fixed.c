#include <assert.h>

// permutes values in a, b and c in order to a
// order a<b<c

void f(short a, short b, short c) {
    short temp;

    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }

    if (b > c) {
        temp = b;
        b = c;
        c = temp;
    }

    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }

    // postcondition to be checked before returning
    // to ensure that permutation is correct
    assert(a <= b && b <= c);
}
