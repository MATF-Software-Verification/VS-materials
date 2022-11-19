#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char *arr1 = calloc(10, 1);
    char *arr2 = malloc(10);
    int *arr3 = calloc(1, sizeof(int));
    write(1 /* stdout */, arr1, 10);
    read(0 /* stdin */, arr2, 10);

    free(arr1);
    free(arr2);

    int x = arr3[0];
    free(arr3);
    exit(x);
}
