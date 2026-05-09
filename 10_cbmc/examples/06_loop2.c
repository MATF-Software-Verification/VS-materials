#include <assert.h>

_Bool f(int i) { return (i + 1) % 23 == 0; }

int main() {
    int i;
    for (i = 0; i < 100; i++) {
        if (f(i))
            break;
    }

    assert(i < 100);
}
