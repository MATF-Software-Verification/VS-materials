#include <assert.h>
#include <limits.h>
#include <stdlib.h>

int abs(int x) {
    int y = x;

    if (x < 0 && x > INT_MIN) {
        y = -x;
    }

    return y;
}
