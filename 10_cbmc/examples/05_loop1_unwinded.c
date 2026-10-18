#include <assert.h>

int main(int argc, char **argv) {
    int i = 1;
    if (i < 5) {
        i = i + 1;
        if (i < 5) {
            i = i + 1;
            if (i < 5) {
                i = i + 1;
                if (i < 5) {
                    i = i + 1;
                    assert(!(i < 5));
                }
            }
        }
    }
}
