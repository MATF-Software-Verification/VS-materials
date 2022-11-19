#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *arr = malloc(10);
    scanf("%s", arr);
    memcpy(arr + 3, arr, strlen(arr));
    printf("%s\n", arr);

    free(arr);
    return 0;
}
