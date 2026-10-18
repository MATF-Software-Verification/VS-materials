/* 1. Write a function that checks if an array of a given length is
 * sorted.
 */
#include <assert.h>
#define MAX 8

int sorted(int *array, int n) {
    int i;

    for (i = 1; i < n; i++)
        if (array[i] < array[i - 1])
            return 0;

    return 1;
}

/* 2. Write a function that creates an array of a given length
 * containing non-deterministic values.
 */
int nondet_int();

void create_array(int *array, int n) {
    int i;

    for (i = 0; i < n; i++)
        array[i] = nondet_int();
}

/* 3. Write a sort function for an array of a given length.
 */

void sort(int *array, int n) {
    int i, j;

    for (i = 0; i < n - 1; i++) {
        int min = i;
        for (j = i + 1; j < n; j++) {
            if (array[j] < array[min])
                min = j;
        }
        if (min != i) {
            int tmp = array[i];
            array[i] = array[min];
            array[min] = tmp;
        }
    }
}

/* 4. Using the code from 1. and 2. create a verification harness and
 * prove that the output of the sort function is actually sorted.
 */

void sortharness() {
    int array[MAX];
    int i;
    int n = nondet_int();
    __CPROVER_assume(n >= 0 && n <= MAX);

    create_array(array, n);
    sort(array, n);

    assert(sorted(array, n) == 1);
}

/* 5. Is the output of 4. sufficient to prove the sort function
 * correct?
 */
