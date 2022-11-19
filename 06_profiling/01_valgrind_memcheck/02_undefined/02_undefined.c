#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char *arr1 = malloc(10);
    char *arr2;
    int *arr3 = malloc(sizeof(int));
    write(1 /* stdout */, arr1, 10);
    read(0 /* stdin */, arr2, 10);
    exit(arr3[0]);
}
