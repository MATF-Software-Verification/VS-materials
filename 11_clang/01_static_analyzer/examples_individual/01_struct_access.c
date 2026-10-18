
struct S {
    int x;
};

void f(struct S s) { char y = s.x; }

void test() {
    struct S *s;
    f(*s);
}

int main() { test(); }
