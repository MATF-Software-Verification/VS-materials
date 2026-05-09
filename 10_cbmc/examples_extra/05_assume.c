
void f() {
    int x = 1;
    if (x > 0) {
        //	__CPROVER_assume (x < 0);

        __CPROVER_assert(x == 0, "assert");
    }
}
