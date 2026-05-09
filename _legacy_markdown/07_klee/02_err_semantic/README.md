## Primer semantičke greške

Pogledajmo primer neispravne funkcije za proveru parnosti celog broja:
```c
int bad_even(int x) {
    if (x % 2 == 0)
        return 1;
    if (x % 2 == 1)
        return 0;
    return 1;
}
```

Ovaj primer, za razliku od prethodnog ima grešku prilikom provere
neparnih negativnih brojeva jer je za njih ostatak pri deljenju jednak
`-1` pa nisu obuhvaćeni drugom `if` naredbom.

Pokušaćemo da korišćenjem KLEE alata otkrijemo ovu grešku i dobijemo
test primer za koji je dostižna poslednja `return` naredba. Kao i
malopre, u glavnom programu označavamo simboličku promenljivu i dodajemo
poziv funkcije `klee_assert(0)` koja će signalizirati grešku pri
eksploatisanju putanje u kojoj je malopređašnja nedostižna naredba.

Nakon dobijanja LLVM bitkoda `bad_even.bc` i pokretanja KLEE alata:
```txt
KLEE: output directory is "klee-out-0"
Using STP solver backend
KLEE: ERROR: bad_even.c:12: ASSERTION FAIL: 0
KLEE: NOTE: now ignoring this error at this location

KLEE: done: total instructions = 39
KLEE: done: completed paths = 3
KLEE: done: generated tests = 3
```

Primetimo da su sada pronađene tri putanje i generisani odgovarajući
test primeri, ali je i prijavljena greška koju je signalizirala funkcija
`klee_assert`. Ukoliko pogledamo sadržaj direktorijuma sa test
primerima, primetićemo da je napravljena datoteka
`test000002.assert.err` koja nam ukazuje da je gore pomenuta greška
signalizirana pri drugom test primeru.

Pogledajmo kakav je ulaz u pitanju:
```sh
$ ktest-tool --write-ints test000002.ktest
```
```txt
ktest file : 'test000002.ktest'
args       : ['bad_even.bc']
num objects: 1
object    0: name: 'x'
object    0: size: 4
object    0: data: -2147483647
```

KLEE je pronašao da je sporna vrednost ulaza `-2147483647`. Upotrebom
debagera i korišćenjem sporne ulazne vrednosti može se uočiti mesto
problema, odnosno da je zaboravljeno da je ostatak pri deljenju sa `2` u
slučaju negativnih brojeva `-1`, a ne `1`. Očekivano, vreme izvršavanja
koje je potrošeno na solver je veće nego u slučaju ispravnog programa.
```sh
$ klee-stats klee-last
```
```txt
------------------------------------------------------------------------
|  Path   |  Instrs|  Time(s)|  ICov(%)|  BCov(%)|  ICount|  TSolver(%)|
------------------------------------------------------------------------
|klee-last|      39|     0.17|    11.30|     7.14|     292|       93.78|
------------------------------------------------------------------------
```
Generalno, prikazanom upotrebom funkcije `klee_assert` možemo označiti
putanju za koju smo zainteresovani, bilo da bismo proverili da li je ta
putanja izvodljiva ili da bismo imali na izlazu označen ulaz kojim se ta
putanja dostiže.
