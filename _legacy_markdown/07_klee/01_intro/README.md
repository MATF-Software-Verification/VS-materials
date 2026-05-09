## Primer upotrebe KLEE alata

Naredni primer (`01_intro`) će nas sprovesti kroz osnovne korake pripreme izvornog
koda za korišćenje alata. Razmotrimo kratak program u kome se testira
funkcija koja proverava da li je učitan ceo broj paran:

```c
int even(int x) {
    if (x % 2 == 0)
        return 1;
    if (x % 2)
        return 0;
    return 1;
}

int main(int argc, char* argv[]) {
    int x;
    scanf("%d", &x);
    printf("%d", even(x));
    return 0;
}
```

Možemo primetiti da je poslednja naredba u definiciji funkcije `even`
nedostižna, odnosno da će se uvek izvršiti prvi ili drugi `return` u
funkciji.

Priprema programa za simboličko izvršavanje:
1. uključiti zaglavlje `klee/klee.h`
1. umesto učitavanja vrednosti promenljive koja nas zanima, označiti je simboličkom pomoću funkcije `klee_make_symbolic`
1. umesto korišćenja eksterne funkcije za ispis koju KLEE ne može da proveri, povratnu vrednost funkcije `even` ćemo vratiti preko povratne vrednosti funkcije `main`

Argumenti funkcije `klee_make_symbolic`, redom:
1.  adresa promenljive
1.  veličina promenljive
1.  naziv promenljive (proizvoljna niska karaktera)

Opciono: primetili smo da je poslednja linija funkcije `even`
nedostižna, ali to možemo i potvrditi pozivom funkcije `klee_assert(0)`,
što će signalizitati grešku alatu ukoliko bude postojala putanja kojom
se dolazi do poziva ove funkcije. U slučaju da takva putanja ne postoji,
neće biti signalizirana greška i potvrdiće se pretpostavka da ne postoji
ulaz za koji je ta naredba dostižna.

**Napomena:** Korišćenje funkcije `klee_assert` zahteva uključivanje zaglavlja `assert.h`.

```c
#include <assert.h>
#include <klee/klee.h>

int even(int x) {
    if (x % 2 == 0)
        return 1;
    if (x % 2)
        return 0;
    klee_assert(0);
    return 1;
}

int main(int argc, char* argv[]) {
    int x;
    klee_make_symbolic(&x, sizeof(x), "x");
    return even(x);
}
```

Pomoću Clang kompilatora generišemo LLVM bitkod koji će biti ulaz za KLEE (Clang će kreirati fajl sa nazivom `even.bc`):

```sh
$ clang -emit-llvm -c -g even.c 
$ klee even.bc
```

```txt
KLEE: output directory is "..."
Using STP solver backend

KLEE: done: total instructions = 42
KLEE: done: completed paths = 2
KLEE: done: generated tests = 2
```

Na osnovu dobijenog izlaza, postoje dve putanje u našem programu, kao
što smo i očekivali, u zavisnosti od toga da li je argument paran ili
neparan po vrednosti. KLEE je generisao direktorijum pod nazivom
`klee-out-0` sa test primerom za svaku eksploatisanu putanju. Pri
sledećem pokretanju generisao bi se direktorijum `klee-out-1`, tj. u
opštem slučaju direktorijum pod nazivom `klee-out-N` za prvo slobodno
`N`. Takođe, napravljen je i simbolički link `klee-last` koji uvek
ukazuje na poslednji `klee-out` direktorijum. Ukoliko izlistamo
direktorijum `klee-out-0`, između ostalog, primetićemo datoteke sa
ekstenzijom `.ktest`. To su binarne datoteke koje sadrže test primere za
svaku putanju zasebno i koje se mogu pročitati korišćenjem alata
`ktest-tool`:

```sh
$ ktest-tool --write-ints test000001.ktest
```

```txt
ktest file : 'test000001.ktest'
args       : ['even.bc']
num objects: 2
object    0: name: 'model_version'
object    0: size: 4
object    0: data: 1
object    1: name: 'x'
object    1: size: 4
object    1: data: 0
```

```sh
$ ktest-tool --write-ints test000002.ktest
```

```txt
ktest file : 'test000002.ktest'
args       : ['even.bc']
num objects: 2
object    0: name: 'model_version'
object    0: size: 4
object    0: data: 1
object    1: name: 'x'
object    1: size: 4
object    1: data: 1
```

Primećujemo da je KLEE generisao ulaz `0` i `1` za pokrivanje dve
otkrivene putanje, tj. jednu parnu i jednu neparnu ulaznu vrednost.

Da bismo proverili da li naš program daje očekivane izlaze za generisane
test primere, možemo testirati polazni program korišćenjem vrednosti
`data` iz pročitanih testova ili koristiti simbolički program
zahvaljujući posebnoj biblioteci `libkleeRuntest` i koja pozive funkcije
`klee_make_symbolic` zamenjuje pozivom funkcije koja promenljivoj
dodeljuje vrednost zapisanu u odgovarajućoj test datoteci.

Testiranje pomoću `libkleeRuntest` biblioteke:
```sh
$ export LD_LIBRARY_PATH=/putanja/do/klee/Release+Asserts/lib
$ gcc \
    -I /putanja/do/klee/include/ \
    -L /putanja/do/klee/Release+Asserts/lib even.c \
    -lkleeRuntest
$ KTEST_FILE=klee-last/test000001.ktest ./a.out
$ echo $?
1
$ KTEST_FILE=klee-last/test000002.ktest ./a.out
$ echo $?
0
```

Očekivano, nismo dobili poruku od `klee_assert` što potvrđuje
pretpostavku da je označen deo koda nedostižan za bilo koji ulaz.

Statističke informacije u vezi sa izvršavanjem KLEE alata nad nekim
bitkodom, kao što su broj izvršenih instrukcija, pokrivenost instukcija
bitkoda, pokrivenost grana bitkoda i slično, možemo dobiti pomoću Python
skripta `klee-stats`. Informacije se prikazuju u tabelarnoj formi. Ovaj
alat se poziva nad direktorijumom koji je generisao KLEE. Da bismo
bili sigurni da je to najnovija verzija direktorijuma, najjednostavnije
je alat pozvati sa argumentom `klee-last`.
```sh
$ klee-stats klee-last
```
```txt
------------------------------------------------------------------------
|  Path   |  Instrs|  Time(s)|  ICov(%)|  BCov(%)|  ICount|  TSolver(%)|
------------------------------------------------------------------------
|klee-last|      42|     0.06|    12.16|     5.71|     296|       90.36|
------------------------------------------------------------------------
```

Legendu za tabelu možemo dobiti pomoću opcije `–help`.

```txt
LEGEND
--------  ---------------------------------------------
Instrs    number of executed instructions
Time      total wall time (s)
ICov      instruction coverage in the LLVM bitcode (%)
BCov      branch coverage in the LLVM bitcode (%)
ICount    total static instructions in the LLVM bitcode
TSolver   time spent in the constraint solver
```

Vizuelni prikaz statistike o simboličkom izvršavanju možemo dobiti
korišćenjem alata *KCachegrind*:

```sh
$ kcachegrind klee-last/run.istats
```

Izborom `CoveredInstructions` ili `UncoveredInstructions` i izborom
kartice `Source Code` možemo tačno videti koje linije jesu, odnosno nisu
pokrivene test primerima.

![kcachegrind_coverage](07_klee/01_intro/images/kcache_coverage.png)

Primetimo da brojevi koje sada vidimo su daleko veći od brojevi koje je
prikazao `klee-stats`. Razlog je to što gcov razmatra samo linije u
jednoj datoteci, a ne u celoj aplikaciji, dok sa KCachegrind-om možemo
čitati izlaz gcov-a o pokrivenosti koda i da ispratimo koje su linije
pokrivene, a koje ne.
