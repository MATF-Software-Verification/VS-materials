#include <assert.h>
#include <klee/klee.h>
#include <stdio.h>

/* funkcija vraca 1 ukoliko je x paran, inace 0 */
int bad_even(int x) {
    if (x % 2 == 0)
        return 1;
    if (x % 2 == 1)
        return 0;

    klee_assert(0); // signalizirace gresku
    return 1;       // sada je naredba dostizna
}

int main() {
    int x;
    /* oznacavamo da je x simbolicka promenljiva:
          argumenti funkcije:
                  - adresa promenljive
                  - velicina
                  - ime (proizvoljna niska karktera)
    */
    klee_make_symbolic(&x, sizeof(x), "x");
    return bad_even(x);
}
