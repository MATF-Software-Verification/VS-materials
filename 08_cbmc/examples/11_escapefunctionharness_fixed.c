#include "10_escapefunction_fixed.c"

char nondet_char(void);

int main(void) {
    char string[16];
    int i;

    for (i = 0; i < 16; ++i) {
        string[i] = nondet_char();
        if (string[i] == '\0') {
            break;
        }
    }

    if (i == 16)
        string[i - 1] = 0;

    char *output = escape(string);

    return 0;
}
