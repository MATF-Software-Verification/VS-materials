#include <stdlib.h>
#include <string.h>

char *escape(const char *s) {
    if (s == NULL)
        return NULL;

    char *escaped = malloc((strlen(s) + 1) * 2 + 1);
    char *output = escaped;

    *(output++) = '"';
    while (*s != '\0') {
        if ((*s == '"') || (*s == '\\')) {
            *(output++) = '\\';
        }
        *(output++) = *(s++);
    }
    *(output++) = '"';
    *(output++) = '\0';

    return escaped;
}
