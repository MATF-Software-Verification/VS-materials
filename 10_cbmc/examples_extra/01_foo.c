int foo(int x, int y) {
    int a[16];
    if (y > 0) {
        if (y < 100) {
            return a[x];
        }
    }
    return -1;
}
