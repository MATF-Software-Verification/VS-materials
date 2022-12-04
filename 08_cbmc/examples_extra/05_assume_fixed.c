s void f() {
    int x = 1;
    if (x > 0) {
        // ne postoji izračunavanje za koje ovo prolazi
        // __CPROVER_assume (x < 0);
        // sve grane stabla izvrsavanja koje ovo ne zadovoljavaju bice odbacene
        // i iz tog razloga nam nece prijaviti gresku, sta god uslov bio

        __CPROVER_assert(x == 0, "assert");
    }
}
