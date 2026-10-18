#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char *source = "sanitizer";
    size_t length = strlen(source);
    char *copy = malloc(length);
    if (copy == NULL) {
        return 1;
    }

    memcpy(copy, source, length + 1);
    puts(copy);
    free(copy);
    return 0;
}
