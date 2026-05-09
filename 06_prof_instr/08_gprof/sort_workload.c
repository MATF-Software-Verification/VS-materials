#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 6000

static void fill_input(int *values, int count) {
    unsigned int x = 0x12345678u;
    for (int i = 0; i < count; i++) {
        x = x * 1103515245u + 12345u;
        values[i] = (int)(x % 100000u);
    }
}

static long checksum(const int *values, int count) {
    long sum = 0;
    for (int i = 0; i < count; i++) {
        sum += values[i] * (i + 1L);
    }
    return sum;
}

static void bubble_sort(int *values, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j + 1 < count - i; j++) {
            if (values[j] > values[j + 1]) {
                int tmp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = tmp;
            }
        }
    }
}

static int compare_ints(const void *left, const void *right) {
    int a = *(const int *)left;
    int b = *(const int *)right;
    return (a > b) - (a < b);
}

static void library_sort(int *values, int count) {
    qsort(values, (size_t)count, sizeof(values[0]), compare_ints);
}

static void run_bubble(const int *input) {
    int *copy = malloc(sizeof(int) * COUNT);
    if (copy == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    memcpy(copy, input, sizeof(int) * COUNT);
    bubble_sort(copy, COUNT);
    printf("bubble checksum=%ld\n", checksum(copy, COUNT));
    free(copy);
}

static void run_library(const int *input) {
    int *copy = malloc(sizeof(int) * COUNT);
    if (copy == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    memcpy(copy, input, sizeof(int) * COUNT);
    library_sort(copy, COUNT);
    printf("qsort checksum=%ld\n", checksum(copy, COUNT));
    free(copy);
}

int main(void) {
    int *input = malloc(sizeof(int) * COUNT);
    if (input == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    fill_input(input, COUNT);
    run_bubble(input);
    run_library(input);

    free(input);
    return 0;
}
