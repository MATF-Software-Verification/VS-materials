#include <stdint.h>
#include <stdlib.h>

int main() {
    char *alphabet = calloc(27, sizeof(char));

    for (int i = 0; i < 26; i++) {
        *(alphabet + i) = 'A' + i;
    }
    *(alphabet + 26) = '\0';

    free(alphabet);
    return 0;
}
