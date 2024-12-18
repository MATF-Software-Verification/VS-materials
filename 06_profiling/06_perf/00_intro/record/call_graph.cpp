#include <cstdint>
#include <cstdio>

double foo(double x) {
    for (int64_t i = 1; i < 1000000; i++) {
        x = x * 1.0001;
    }

    return x;
}

double bar(double x) {
    for (int64_t i = 1; i < 500000; i++) {
        x = x * 1.0001;
    }

    return x;
}

double master(double x) { return foo(x) + bar(x); }

int main() {
    printf("val: %f\n", master(23));
    printf("val: %f\n", bar(45));
}
