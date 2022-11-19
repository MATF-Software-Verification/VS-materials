#include <stdint.h>
#include <stdlib.h>

struct _List {
    int *data;
    int length;
};
typedef struct _List List;

List *resizeArray(List *array) {
    int *dPtr = array->data;
    dPtr = realloc(dPtr, 15 * sizeof(int));
    return array;
}

int main() {
    List *array = calloc(1, sizeof(List));
    array->data = calloc(10, sizeof(int));
    array = resizeArray(array);

    free(array->data);
    free(array);
    return 0;
}
