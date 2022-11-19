#include <stdio.h>
#include <stdlib.h>

int main() {
    char *p, q;

    p = (char *)malloc(19);
    p = (char *)malloc(12);
    free(p);
    free(p);

    p = &q;
    free(p);

    return 0;
}
