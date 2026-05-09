#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void load_line(const char *text) {
    char *line = malloc(strlen(text) + 1);
    if (line == NULL) {
        exit(1);
    }

    strcpy(line, text);
    printf("%c\n", line[0]);
}

int main(void) {
    load_line("verification");
    load_line("sanitizer");
    load_line("leak");
    return 0;
}
