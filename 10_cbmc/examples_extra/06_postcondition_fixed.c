int nondet_int();
int N, x;

int main() {
    N = nondet_int();
    x = nondet_int();
    int i = N;

    while (0 <= x && x < N) {
        i = i - 1;
        x = x + 1;
    }
    __CPROVER_assert(0 <= i, "postcondition");
}
