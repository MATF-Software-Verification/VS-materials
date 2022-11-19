#include <stdio.h>
#include <stdlib.h>

int main() {
    char *p, q;

    p = (char *)malloc(19);
    free(p);
    p = (char *)malloc(12);
    free(p);

    p = &q;
    // free(p);

    return 0;
}
