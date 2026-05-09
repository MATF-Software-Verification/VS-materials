#include <stdio.h>

int isPrime(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int primeCount = 0;
    int x;

    printf("Insert number: ");
    scanf("%d", x);

    if (x > 80 || x < 2)
        return 0;

    int no = isPrime(x);

    if (no) {
        printf("%d is a prime number\n", x);
    } else
        printf("%d is not a prime\n", x);

    return 0;
}
