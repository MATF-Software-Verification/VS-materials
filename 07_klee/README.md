# KLEE

[KLEE](http://klee.github.io/) je javno dostupan alat koji se distribuira pod licencom NCSA
otvorenog koda Univerziteta Ilinois. Služi za simboličko izvršavanje
programa i za automatsko generisanje test primera. KLEE vrši analizu
nad LLVM međureprezentacijom i koristi SMT rešavač [STP](https://stp.github.io/) za proveravanje uslova
ispravnosti koje generiše. KLEE koristi nekoliko optimizacija i
heuristika za poboljšavanje pokrivenosti koda prilikom simboličkog
izvršavanja. KLEE se koristi i kao sastavni deo raznih platformi za
razvijanje novih alata za analizu programa. KLEE ima dva cilja:
1. da pokrije svaku liniju izvornog koda u programu
1. da detektuje svaku opasnu operaciju ako postoji ijedna ulazna vrednost koja može da prouzrokuje grešku

Ukoliko prilikom generisanja test primera za neku od putanja, KLEE pronađe test primer koji izaziva grešku, onda će pored tog test primera
biti generisane još dve datoteke:
-   `test<N>.pc` - uslovi ograničenja koji važe za tu putanju i koji su
    prosleđeni solveru u `KQuery` sintaksi [@kquery].
-   `test<N>.<TYPE>.err` - dodatne informacije o grešci

`<TYPE>` označava tip detektovane greške. Neke od grešaka koje KLEE
može da detektuje su:
-   **ptr**: Čitanje ili pisanje u nevalidnu memorijsku lokaciju;
-   **free**: Dupli ili nekorektan poziv funkcije `free()`;
-   **abort**: Program je pozvao funkciju `abort()`;
-   **assert**: Uslov proveravan funkcijom `assert` nije tačan;
-   **div**: Deljenje nulom ili računanje po modulu 0;
-   **user**: Problem je u vezi sa ulazom (neispravan poziv
    `klee intrinsic`) ili pogrešan način upotrebe KLEE-a.
-   **exec**: Dogodio se problem koji je KLEE sprečio u izvršavanju
    programa, npr. nepoznata instrukcija, poziv preko neispravnog
    pokazivača na funkciju ili inline funkcije.
-   **model**: KLEE nije mogao da ispuni kompletnu preciznost i
    ispituje samo deo svih stanja programa. Na primer, simboličke
    veličine prosleđene `malloc` funkciji nisu trenutno podržane i u
    takvim situacijama KLEE konkretizuje taj argument.
