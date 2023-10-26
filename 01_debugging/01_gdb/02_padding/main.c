#include <stdio.h>
#include <stdlib.h>

int main() {
    struct A { 
        int x;          // sizeof(int) = 4 
                        // 4 byte padding 
        double z;       // sizeof(double) = 8 
        
        short int y;    // sizeof(short int) = 2 
                        // 6 byte padding 
    }; 
    printf("Size of A: %ld\n", sizeof(struct A)); 

    struct B { 
        double z;       // sizeof(double) = 8 
        
        int x;          // sizeof(int) = 4 

        short int y;    // sizeof(short int) = 2 
                        // 2 byte padding 
    };
    printf("Size of B: %ld\n", sizeof(struct B)); 

    struct C { 
        double z;       // sizeof(double) = 8 
        
        short int y;    // sizeof(short int) = 2 
                        // 2 byte padding 
        int x;          // sizeof(int) = 4 
    };
    printf("Size of C: %ld\n", sizeof(struct C)); 

    return 0;
}
