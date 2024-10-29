#include <stdio.h>
#include <stdlib.h>

/*
 * Rules:
    char and char[] are special, could be any memory address, so they don't need
 padding before them. E.g., on many systems, if struct's largest member is int
 then by divisible by 4, if short then by 2.
 */
int main() {
    struct A {
        // Before each individual member, there will
        // be padding so that to make it start at an
        // address that is divisible by its alignment
        // requirement (except char and char[]).

        int x; // sizeof(int) = 4

        // 4 byte padding
        double z; // sizeof(double) = 8

        short int y; // sizeof(short int) = 2

        // The size of whole struct will be padded to
        // a size divisible by strictest alignment
        // requirement of any of its members.

        // 4 + 4 + 8 + 2 = 18
        // strictest alignment is double (8)
        // so next number divisible by 8 is 24
        // hence:

        // 6 byte padding
    };
    printf("Size of A: %ld\n", sizeof(struct A));

    struct B {
        double z; // sizeof(double) = 8

        int x; // sizeof(int) = 4

        short int y; // sizeof(short int) = 2
                     // 2 byte padding
    };
    printf("Size of B: %ld\n", sizeof(struct B));

    struct C {
        double z; // sizeof(double) = 8

        short int y; // sizeof(short int) = 2
                     // 2 byte padding
        int x;       // sizeof(int) = 4
    };
    printf("Size of C: %ld\n", sizeof(struct C));

    // Note: It is possible to disable padding, via
    // a process called "packing", which has to be
    // explicitly requested, e.g., with GCC attrs:
    // struct __attribute__((__packed__)) mystruct_A {
    //     char a;
    //     int b;
    //     char c;
    // };
    // ^ this struct would have size 6

    return 0;
}
