# Ograničena provera modela (alat CBMC)

Provera modela je tehnika verifikacije softvera kojom se određuju sve
moguće putanje kroz program i čuvaju u vidu konačnog automata. Zatim se
prati svaka putanja i vrše se provere. Većina alata otkriva osnovne
greške: deljenje nulom, mrtve petlje, trku za podacima itd.

Kod provere modela, program koji treba da se verifikuje je modelovan u
vidu konačnog automata i specifikacija je zadata temporalnom logikom.
Glavna ideja ograničene provere modela (engl. *bounded model checking*)
da pronađe kontraprimer u izvršavanjima čija dužina je ograničena celim
brojem `k`. Ako greška nije prijavljena, možemo povećavati `k` sve dok,
ili greška ne bude nađena, ili problem više ne može da se prati, ili se
dostigne neko drugo ranije definisano gornje ograničenje modela. Problem
provere modela se efikasno može svesti na problem zadovoljivosti iskazne
logike i kao takav može biti rešen SAT rešavačem. Moderni SAT rešavači
rešavaju probleme i sa više stotina hiljada promenljivih.

Ograničena provera modela ima dve karakteristike:
-   korisnik obezbeđuje ograničenje broja ciklusa koje treba istražiti,
    samim tim tehnika je nepotpuna ako je ograničenje nedovoljno visoko
-   koristi SAT tehnike.

Proverom modela automatski se pronalaze sve putanje koje se mogu
izvršiti i čuvaju u internom modelu. Zatim se izvršava svaka putanja
internog modela i proverava pojavljuju li se osnovne greške i da li su
ispunjena svojstva modela. Svojstva modela se mogu zadati temporalnom
logikom. Neki od operatora temporalne logike, za iskaze `p` i `q`:
-   `Fp` - `p` važi neko vreme u budućnosti
-   `Gp` - `p` važi uvek u budućnosti
-   `Xp` - `p` važi sledeći put
-   `p ∪ q` - `p` važi dok `q` važi

Primer upotrebe operatora bi mogao da bude: Automobil ne kreće dok je
menjač u poziciji *Parking*.

```txt
(~start) U gear_park
```

## Primer sa mikrotalasnom rernom

Uzmimo primer programa koji simulira rad mikrotalasne rerne. Svojstva
koja moraju biti ispunjena:
-   ako su vrata zatvorena, mogu biti otvorena.
-   ako su vrata otvorena, mogu buti zatvorena.
-   ako je grejač isključen, može biti uključen, ali samo ako su vrata
    zatvorena.
-   ako je grejač uključen, može biti isključen.

Ove zahteve možemo predstaviti programom:

```java
public class Microwave {
    boolean doorOpen = false;
    boolean heatOn = false;

    public Microwave() {}

    public void openDoor() {
        if (!doorOpen) doorOpen = true;
    }
 
    public void closeDoor() {
        if (doorOpen) doorOpen = false;
    }

    public void turnHeatOn() {
        if (!heatOn && !orOpen) heatOn = true;
    }

    public void turnHeatOff() {
        if (heatOn) heatOn = false;
    }
}
```

Program dozvoljava otvaranje i zatvaranje vrata kao i paljenje i gašenje
grejača. Kao zaštitno svojstvo, postoji provera da li su vrata zatvorena
pre nego što se grejač uključi, inače ga neće uključiti. Kreirajmo
konačni automat za ove funkcionalnosti:

![automata](08_cbmc/images/automata1.png)

Dijagram na slici prikazuje kako se stanje program menja, tj.
vrednosti promenljivih `doorOpen` i `heatOn`. Sastavimo kompletan dijagram:

![automata](08_cbmc/images/automata2.png)

Na slici vidimo četiri stanja sa različitim vrednostima dve
logičke promenljive u obliku krugova. Sistem može menjati stanje
korišćenjem nekog od metoda klase. Imamo opasno stanje `S2` u kom su
vrata otvorena i grejač uključen. U ovo stanje nije moguće doći pozivom
metode `turnHeatOn()` iz stanja S3 jer je metoda tako napisana da ne
uključuje grejač ako su vrata otvorena. Ipak, sistem može doći u sporno
stanje `S2`, tako što prvo dođe u stanje `S1` i zatim pozove metod
`doorOpen()` dok je grejač već uključen. Ta putanja možda nije uočljiva 
iz koda ili sa prvog automata. Međutim, postaje jasno vidljiva kada se 
napravi dijagram svih stanja.

Kada se kreira model programa i lista svojstava, moguće je ispratiti
svaku moguću putanju i proveriti ispravnost svih svojstava.

U slučaju da promenljive programa mogu uzeti više vrednosti, bilo bi
mnogo više stanja u modelu. Tada se koristi mnogo više memorije, pa
možda i sva memorija u kompjuteru. Ova pojava se zove eksplozija
prostora stanja i to je i dalje aktivan problem za proveru modela.

Neki od alata za proveru modela shodno programskom jeziku:
- Java: NASA's PathFinder, BANDERA, CBMC, DBRover
- C/C++: BLAST, CBMC, PCAchecker, DBRover, DSVerifier, ESBMC, SATABS

## CBMC

Alat [CBMC](https://www.cprover.org/cbmc/), kao i kompajleri, 
traži `.c` datoteku kao argument komandne linije. Prevodi program i 
objedinjuje ga sa definicijima drugih funkcija iz više `.c` datoteka, 
poput linkera. Ipak, umesto da proizvede izvršivu verziju programa, 
CBMC sprovodi simboličko izvršavanje programa.

![cbmc](08_cbmc/images/cbmc.png)


### Primer sa argumentima komandne linije

Kao primer, razmotrimo program `01_file1.c`:

```c
int puts(const char *s) { }

int main(int argc, char **argv) {
    puts(argv[2]);
}
```

Očigledno je da program ima grešku, jer niz `argv` može imati i manje od
3 elementa i da se sa `argv[2]` izlazi izvan okvira niza. Pokrenimo
CBMC sledećom komandom:
```sh
$ cbmc 01_file1.c --show-properties --bounds-check --pointer-check
```

Opcije `–bounds-check` i `–pointer-check` navode CBMC da traži greške
u vezi pokazivača ili granica nizova. Zbog opcije `–show-properties`
CBMC će štampati listu svih svojstava koje proverava. Prikazuje,
između ostalog i svojstvo `"object bounds in argv"` zajedno sa lokacijom
pogrešnog pristupa elementu niza. CBMC uglavnom određuje svojstva koja
treba da proveri. To se postiže preliminarnom statičkom analizom, koju
vrši generator tvrđenja (engl. *assertion generator*) *goto-instrument*
da označi deo koda koji potencijalno sadrži grešku.

Generator tvrđenja generiše tvrđenja za verifikaciju sledećih svojstava:
- **Prekoračenje bafera** - Za svaki pristup elementu niza, proverava
    se da li je narušena donja ili gornja granica (opcija
    `–bound-check`).
- **Upotreba pokazivača** - Traži dereferenciranje `NULL` ili
    neispravnih pokazivača (opcija `–pointer-check`).
- **Deljenje nulom** - Proverava da li u programu postoji deljenje
    nulom (opcija `–div-by-zero-check`).
- **Aritmetička potkoračenja i prekoračenja** - Proverava da li je
    došlo do prekoračenja ili potkoračenja prilikom aritmetičkih
    operacija nad označenim i neoznačenim brojevima (opcije
    `–signed-overflow-check` i `–unsigned-overflow-check`) ili realnim
    brojevima (opcija `–float-overflow-check`).
- **Nije broj** - Proverava da li je račun sa realnim brojevima može
    rezultovati `NaN` vrednosti (opcija `–nan-check`).
- **Neinicijalizovana promenljiva** - Proverava da li program koristi
    lokalnu promenljivu pre nego što je inicijalizovana.
- **Trka za podacima** - Proverava da li dve niti programa pristupaju
    istoj deljenoj promenljivoj u isto vreme.

Daljom analizom je potrebno utrvditi da li su to zaista greške.
CBMC-ovu analizu sprovodi simboličkom simulacijom, koja odgovara
translaciji programa u formulu. Ta formula se kombinuje sa svojstvom.
Generisanu formulu možemo videti navođenjem opcije `–show-vcc`. (engl.
*Verification Condition*).
```sh
$ cbmc 01_file1.c --show-vcc --pointer-check
```

Prilikom analize generiše se KNF formula koja opisuje program, zajedno
sa svojstvima. Izgleda kao izraz koja zadovoljava i uslove problema i
negaciju tvrđenja. Formula se prosleđuje SAT rešavaču koji donosi odluku
da je formula zadovoljiva (i tako nam pronalazi kontraprimer) ili je
nezadovoljiva i time tvrđenje važi za izvršenje sa ograničenjem `k`.

Formula, odnosno uslovi verifikacije, treba tek da budu provereni da bi
se proverilo da li važi navedeno svojstvo. Pokrećemo sa:
```sh
$ cbmc 01_file1.c --pointer-check
```

Korišćenjem SAT rešavača, CBMC detektuje da ne važi uslov za granice
niza `argv` i štampa sledeću poruku:
```txt
Violated property:
  file 01_file1.c line 7 function main
  dereference failure: object bounds in argv[(signed long int)2]
```

Da bismo razumeli problem i zašto svojstvo ne važi, CBMC može da nam
generiše kontraprimerov trag izvršavanja programa korišćenjem opcije
`–trace`:
```sh
$ cbmc 01_file1.c --pointer-check --trace
```

Na ekranu nam se prikazuje kontraprimer, u vidu toka izvršavanja
programa počevši od `main` funkcije do stanja koje narušava svojstvo. U
ovom primeru svojstvo je narušeno u neispravnom indeksiranju elementa
niza. Takođe, prikazuje nam i vrednosti koje ulazne promenljive treba da
imaju da bi se izazvala greška. Prikazuje nam i uslov čijom proverom se
došlo do zaključka.
```txt
CBMC version 5.10 (cbmc-5.10) 64-bit x86_64 linux
Parsing 01_file1.c
Converting
Type-checking 01_file1
Generating GOTO Program
Adding CPROVER library (x86_64)
Removal of function pointers and virtual functions
Generic Property Instrumentation
Running with 8 object bits, 56 offset bits (default)
Starting Bounded Model Checking
size of program expression: 43 steps
simple slicing removed 10 assignments
Generated 7 VCC(s), 1 remaining after simplification
Passing problem to propositional reduction
converting SSA
Running propositional reduction
Post-processing
Solving with MiniSAT 2.2.1 with simplifier
462 variables, 1031 clauses
SAT checker: instance is SATISFIABLE
Solving with MiniSAT 2.2.1 with simplifier
462 variables, 0 clauses
SAT checker inconsistent: instance is UNSATISFIABLE
Runtime decision procedure: 0.00274368s

** Results:
[main.pointer_dereference.1] dereference failure: pointer NULL in argv[(signed long int)2]: SUCCESS
[main.pointer_dereference.2] dereference failure: pointer invalid in argv[(signed long int)2]: SUCCESS
[main.pointer_dereference.3] dereference failure: deallocated dynamic object in argv[(signed long int)2]: SUCCESS
[main.pointer_dereference.4] dereference failure: dead object in argv[(signed long int)2]: SUCCESS
[main.pointer_dereference.5] dereference failure: pointer outside dynamic object bounds in argv[(signed long int)2]: SUCCESS
[main.pointer_dereference.6] dereference failure: pointer outside object bounds in argv[(signed long int)2]: FAILURE
[main.pointer_dereference.7] dereference failure: invalid integer address in argv[(signed long int)2]: SUCCESS

Trace for main.pointer_dereference.6:

State 17  thread 0
----------------------------------------------------
    INPUT argc: 1 (00000000 00000000 00000000 00000001)

State 18  thread 0
----------------------------------------------------
    argv'[1]=((char *)NULL) (00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000)

State 21 file 01_file1.c line 3 thread 0
----------------------------------------------------
    argc=1 (00000000 00000000 00000000 00000001)

State 22 file 01_file1.c line 3 thread 0
----------------------------------------------------
    argv=argv' (00000010 00000000 00000000 00000000 00000000 00000000 00000000 00000000)

Violated property:
    file 01_file1.c line 5 function main
    dereference failure: pointer outside object bounds in argv[(signed long int)2]
    16l + POINTER_OFFSET(argv) >= 0l && OBJECT_SIZE(argv) >= 24ul + (unsigned long int)POINTER_OFFSET(argv) || DYNAMIC_OBJECT(argv)


** 1 of 7 failed (2 iterations)
VERIFICATION FAILED
```

U ovom primeru, ako je `argc == 1` dogodiće se prekoračenje granica niza
`argv`. Ako dodamo proveru uslova da je `argc >= 3`, greška je otklonjena
i CBMC-ov izveštaj dokazuje da su sva svojstva zadovoljena.


### Primer odvojenog testiranja funkcija

CBMC je pisan sa namerom da se koristi i za ugrađen softver, a takvi
programi imaju obično drugačije ulaze tačke od `main` funkcije. Pored
toga CBMC je vrlo koristan za verifikaciju modula programa, poput ovog
primera.
```c
int array[10];

int sum() {
    unsigned i, sum = 0;
    for (i = 0; i < 10; i++)
        sum += array[i];
}
```

Potrebno je CBMC-u da naglasimo koja je ulazna tačka, a to je ovde
funkcija `sum`. Pozivamo CBMC sa sledećim opcijama:
```sh
$ cbmc 02_file2.c --function sum --bounds-check
```

Često je potrebno napraviti odgovarajuće propratne alate (*eng.
harness*) za funkciju da bi se podesilo odgovarajuće okruženje.

U ovom primeru možemo da primetimo i da CBMC odmotava petlju iz
programa. Kako CBMC šalje svoju formulu SAT rešavaču ona mora biti
konačna, tako i CBMC izvršava ograničenu proveru modela. Stoga se
petljama broj iteracija mora ograničiti odozgo da bi se garantovalo
pronalaženje grešaka. CBMC može proveriti da li je dovoljno
odmotavanja izvršeno.

Svaka druga petlja (`for`, `do-while`) biće prezapisana u `while`
petlju.

Treba znati da su globalne promenljive inicijalizovane pre izvršavanja
date funkcije, što može dovesti do drugačijih stanja od onih prilikom
realnog izvršavanja funkcije. CBMC ne pokušava da odredi preduslove za
argumente funkcije.


### Primer neuspelog odmotavanja petlji

```c
int binsearch(int x) {
    int a[16];
    signed low = 0, high = 16;

    while (low < high) {
        signed middle = low + ((high - low) >> 1);

        if (a[middle] < x)
            high = middle;
        else if (a[middle] > x)
            low = middle + 1;
        else // a[middle] == x
            return middle;
    }

    return -1;
}
```
Pokrenimo CBMC:
```sh
$ cbmc 03_binsearch.c --function binsearch --bounds-check
```

Primetićemo da se odmotavanje petlje ne zaustavlja samo od sebe jer
CBMC ne uspeva da otkrije gornje ograničenje za broj iteracija ove
petlje. U tom slučaju gornje ograničenje za odmotavanje petlje mora da
se zada preko opcije `–unwind n`, gde `n` zapravo predstavlja broj
provera uslova ostanka u petlji:
```sh
$ cbmc 03_binsearch.c --function binsearch --unwind 6  --bounds-check
```

CBMC potvrđuje da su svi pristupi elementima niza u okviru granica
iako to u ovom slučaju zavisi od šiftovanja u desno. Ukoliko se upotrebi
opcija `–unwinding-assertions`, proveravaće da li je dovoljno odmotana
petlja. Za kraća odmotavanja od 6 bili bi ispisani koraci izvršavanja
koji zahtevaju više odmotavanja petlje. Ukoliko je pozvan i sa opcijom
`–trace`, generisaće nam i kontraprimer.
```sh
$ cbmc 03_binsearch.c --function binsearch --unwind 5 --unwinding-assertions  --bounds-check --trace
```
```txt
[binsearch.unwind.0] unwinding assertion loop 0: FAILURE

** 1 of 5 failed (2 iterations)
VERIFICATION FAILED
```

### Primer sa neograničenim petljama

CBMC se može primeniti i na program sa neograničenim petljama. U
takvim situacijama, CBMC služi samo za traženje grešaka i ne pokušava
da pronađe sve. Program `04_lock-example.c` je primer programa sa
svojstvom koje je korisnik definisao, navodeći `assert` naredbe u kodu.

`while` petlja nema konkretnu gornju granicu broja iteracija. Stoga,
mora se naglasiti koliko odmotavanja petlje treba CBMC da izvrši.
Postoje dva načina da se tako nešto postigne:
-   opcijom `–unwind` da se ograniči koliko puta su pelje odmotane.
-   opcijom `–depth` da se ograniči broj koraka program koje treba
    pratiti.

Ukoliko navedemo i opciju `–unwinding-assertions`, CBMC će proveriti
da li je argument uz opciju `–unwind` dovoljno veliki da pokrije sve
putanje kroz program. Ukoliko je premali, detektovaće nam da nije
dovoljno odmotavanja izvršeno.

Vratimo se na primer i pokrenimo CBMC:
```sh
$ cbmc 04_lock-example.c  --unwind 1 --unwinding-assertions
```

Ne prijavljuje nam grešku (osim da imamo premalo odmotavanja). Ukoliko se
izostavi poslednja opcija, neće ni to prijavljivati. Već sa ograničenjem
`2`, CBMC detektuje grešku. Upotrebom opcije `–trace` generisaće nam se
kontraprimer koji narušava važenje tvrđenja, (*eng. assertion*).
```sh
$ cbmc 04_lock-example.c  --unwind 1 --trace
```

Bez prijave o nedovoljnom odmotavanju petlje ili korišćenjem opcije
`–depth`, CBMC ne dokazuje korektnost programa, ali je i dalje
koristan za nalaženje grešaka.

Pokrećemo CBMC ponovo sa ciljem da proverimo ima li program grešaka.
```sh
$ cbmc 04_lock-example.c  --unwind 1
```

Jedinu grešku koju dobijamo je da smatra da petlja nije odmotana do
kraja. Zato pokrećemo ponovo sa većim brojem iteracija.
```sh
$ cbmc 04_lock-example.c  --unwind 2
```

Dobijamo grešku da korisnikovo tvrđenje ne važi:
```txt
** Results:
[lock.assertion.1] assertion !(LOCK != FALSE): SUCCESS
[unlock.assertion.1] assertion LOCK: FAILURE

** 1 of 2 failed (2 iterations)
VERIFICATION FAILED
```

Generišimo i kontraprimer pozivom :
```sh
$ cbmc 04_lock-example.c  --unwind 2 --trace
```
```txt
Counterexample:

State 19 file lock-example.c line 19 function main thread 0
----------------------------------------------------
    got_lock=0 (00000000000000000000000000000000)

State 20 file lock-example.c line 19 function main thread 0
----------------------------------------------------
    got_lock=0 (00000000000000000000000000000000)

State 21 file lock-example.c line 20 function main thread 0
----------------------------------------------------
    times=1713006976 (01100110000110100110100110000000)

State 35 file lock-example.c line 32 function main thread 0
----------------------------------------------------
    got_lock=4294967295 (11111111111111111111111111111111)

State 36 file lock-example.c line 32 function main thread 0
----------------------------------------------------
    times=1713006975 (01100110000110100110100101111111)
```

Shvatamo da se u toj jednoj iteraciji naše petlje dogodilo da je
izvršena linija `32` i smanjena vrednost od `get_lock`, a s obzirom da je tip
`unsigned int`, dobila je vrednost najvećeg neoznačenog celog broja. To ne
sme da se dogodi, jer je smisao te promenljive da se poveća kada se
ostvari zaključavanje i da se smanji na `0` kada se otključa. Izmenimo kod
i primetimo da više neće prijavljivati problem.


### Odmotovanje zasnovano na broju iteracija

Pogledajmo primer `05_loop1.c`
```c
int main(int argc, char **argv) {
    int i = 1;
    while (i < 5) {
        i = i + 1;
    }
    return 0;
}
```

Ovo bi bio primer programa u kome je dovoljno da imamo 5 odmotavanja
petlje. Transformisan program bez petlje izgleda ovako:
`05_loop1_unwinded.c`
```c
#include <assert.h>

int main(int argc, char **argv) {
    int i = 1;  
    if (i < 5) {
        i = i + 1;
        if (i < 5) {
            i = i + 1;
            if (i < 5) {
                i = i + 1;
                if (i < 5) {
                    i = i + 1;
                    assert(!(i < 5));
                }
            }
        }
    }
}
```
Program odgovara toku izvršavanja petlje sa 4 iteracije, a uslov ostanka
u petlji se 5 puta proverava. Odgovara pozivu:
```sh
$ cbmc 05_loop1.c  --unwind 5 --unwinding-assertions
```

 Za svaki manji broj odmotavanja, manji od 5, prijavio bi nedovoljno
odmotavanje. Transformisan kod za 3 odmotavanja bi izgledao ovako:
`05_loop1_unwinded_insufficently.c`
```c
#include <assert.h>

int main(int argc, char **argv) {
    int i = 1;  
    if (i < 5) {
        i = i + 1;
        if (i < 5) {
            i = i + 1;
            assert(!(i < 5));
        }
    }
}
```

Odgovara pozivu:
```sh
$ cbmc 05_loop1.c  --unwind 2 --unwinding-assertions
```

Ukoliko ograničimo razmotavanje petlje, i pri tom ne navedemo opciju
`–unwinding-assertions` , posle određenog broja iteracija, pretpostaviće
se da više ne važi uslov ostanka u petlji i nastaviće se dalje. Dakle
sve preostale putanje kroz petlju biće ignorisane.
```c
#include <assert.h>

int main(int argc, char **argv) {
    int i = 1;  
    if (i < 5) {
        i = i + 1;
        if (i < 5) {
            i = i + 1;
            assume(!(i < 5));
        }
    }
}
```

U mnogim slučajevima CBMC može da automatski odredi gornju granicu
iteracija petlje, pa i u slučajevima kada broj odmotavanja petlje nije
konstanta. Primer `06_loop2.c` to prikazuje:
```c
#include <assert.h>

_Bool f(int i){
    return (i+1) % 23 == 0;
}

int main() {
    int i;
    for (i = 0; i < 100; i++) {
        if (f(i)) break;
    }
    assert(i<100);
}
```

`while` petlja ima očigledno gornje ograničenje za broj iteracija, ali
iz petlje se može i ranije izaći u zavisnosti od povratne vrednosti
funkcije `f()`.CBMC može automatski da odmota petlju do završetka. To
automatsko detektovanje granice odmotavanja petlji može biti neuspešno
ukoliko broj iteracija petlje veoma zavisi od podataka. Takođe, broj
iteracija može biti i mnogo veliki ili jednostavno neograničen. U tim
slučajevima je bolje korisiti opciju komandne linije ` –unwind B`, gde
`B` označava broj provera uslova ostanka u petlji tj. skokova na
početak. Tada se telo petlje izvršava `B-1` put.


### Zadavanje ograničenja odmotavanja za pojedinačne petlje

Upotrebom opcije `–unwind` ograničenje za odmotavanje se namešta
globalno, za sve petlje u programu. Pogledajmo primer `07_loop3.c`:
```c
#include <assert.h>

_Bool f(int i){
    return (i+1)%23 == 0  ;
}

int main() {
    int i;
    for (i = 0; i < 100; i++) {
        if (f(i)) break;
    }
 
    for (i = 0; i < 100; i++) {
        if (f(i*2)) break;
    }
    
    assert(i<100);
}
```

Da bismo zadali za svaku petlju posebno ograničenje prvo pokrenim
program sa opcijom `–show-loops` da bismo dobili listu svih pelji u
programu i njihove identifikatore.
```sh
$ cbmc 07_loop3.c --show-loops
```
```txt
CBMC version 5.10 (cbmc-5.10) 64-bit x86_64 linux
Parsing 07_loop3.c
Converting
Type-checking 07_loop3
Generating GOTO Program
Adding CPROVER library (x86_64)
Removal of function pointers and virtual functions
Generic Property Instrumentation
Loop main.0:
    file 07_loop3.c line 9 function main

Loop main.1:
    file 07_loop3.c line 13 function main
```

Za program sa 2 petlje zadajemo ograničenja odmotavanja za petlje redom,
10, odnosno 20, opcijom `–unwindset`.
```sh
$ cbmc 07_loop3.c --unwindset main.0:10,main.1:20 --unwinding-assertions
```
```txt
CBMC version 5.10 (cbmc-5.10) 64-bit x86_64 linux
Parsing 07_loop3.c
Converting
Type-checking 07_loop3
Generating GOTO Program
Adding CPROVER library (x86_64)
Removal of function pointers and virtual functions
Generic Property Instrumentation
Running with 8 object bits, 56 offset bits (default)
Starting Bounded Model Checking
Unwinding loop main.0 iteration 1 file 07_loop3.c line 9 function main thread 0
Unwinding loop main.0 iteration 2 file 07_loop3.c line 9 function main thread 0
Unwinding loop main.0 iteration 3 file 07_loop3.c line 9 function main thread 0
Unwinding loop main.0 iteration 4 file 07_loop3.c line 9 function main thread 0
Unwinding loop main.0 iteration 5 file 07_loop3.c line 9 function main thread 0
Unwinding loop main.0 iteration 6 file 07_loop3.c line 9 function main thread 0
Unwinding loop main.0 iteration 7 file 07_loop3.c line 9 function main thread 0
Unwinding loop main.0 iteration 8 file 07_loop3.c line 9 function main thread 0
Unwinding loop main.0 iteration 9 file 07_loop3.c line 9 function main thread 0
Not unwinding loop main.0 iteration 10 file 07_loop3.c line 9 function main thread 0
size of program expression: 140 steps
simple slicing removed 2 assignments
Generated 1 VCC(s), 1 remaining after simplification
Passing problem to propositional reduction
converting SSA
Running propositional reduction
Post-processing
Solving with MiniSAT 2.2.1 with simplifier
120 variables, 11 clauses
SAT checker: instance is SATISFIABLE
Solving with MiniSAT 2.2.1 with simplifier
120 variables, 0 clauses
SAT checker inconsistent: instance is UNSATISFIABLE
Runtime decision procedure: 0.00124571s

** Results:
[main.assertion.1] assertion i<100: SUCCESS
[main.unwind.0] unwinding assertion loop 0: FAILURE

** 1 of 2 failed (2 iterations)
VERIFICATION FAILED
```

### Odsecanje petlji

U nekim slučajevima je poželjno da odsečemo veoma duboke petlje u cilju
dostizanja koda koji dolazi posle petlje. Pogledajmo primer `08_loop4.c`:

```c
#include <assert.h>
#include <stdio.h>

int main() {
    int i;
    for (i = 0; i < 10000; i++) {
        printf("i = %d\n", i);
    }
 
    assert(0);
}
```

U ovom primeru za malo ograničenje odmotavanja petlje provera posle
petlje neće biti izvršena. Ako se smatra da neka petlja nije bitna za
kod koji sledi posle nje, možemo koristiti opciju ` –partial-loops`. Ova
opcija dozvoljava da se delimično izvrše putanje kroz petlju i time i za
mala ograničenja odmotavanja pronalazi se kontraprimer za proveru koja
se izvršava posle petlje.
```sh
$ cbmc 08_loop4.c  --unwind 1 --partial-loops
```

Problem sa delimičnim izvršavanjem petlje je što putanja koja na kraju
bude izvršena ne mora biti jedna od validnih putanja kroz petlju u
originalnom programu. Opcijom `–partial-loops` stavlja se `break`
naredba na mestu gde stoji `assert`, odnosno `assume`, prilikom
ograničenog razmotavanja petlje sa opcijom `–unwinding-assertions`,
odnosno bez nje.

Pozivom:
```sh
$ cbmc 08_loop4.c  --unwind 10
```
se ne dolazi do provere `assert` i ne detektuje se greška. Potrebno je
da se petlja razmota 10001 put, da bi se stiglo do ostatka programa.


### Odmotavanje zasnovano na dubini (Depth-based Unwinding)

Ograničenje za broj odmotavanja petlje nekada nije dovoljno. U
situacijama kada je teško kontrolisati veličinu generisane formule samo
opcijom `–unwind` option. Tada opcijom ` –depth D` zadajemo da je
odmotavanje petlje ograničeno brojem instrukcija koje su izvršene na toj
putanji, nebitno od rednog broja iteracija petlje. CBMC koristi broj
instrukcija u grafu kontrole toka (*eng. control flow graph*), a ne broj
instrukcija u izvornom kodu.

### Dekompozicija koraka analize

Instrumentacija:
```sh
$ cbmc 09_abs.c –function abs –signed-overflow-check –show-goto-functions`
```
Svojstva:
```sh
$ cbmc 09_abs.c –function abs –signed-overflow-check –show-properties
```
Static Single Assign (SSA):
```sh
$ cbmc 09_abs.c –function abs –signed-overflow-check –program-only
```
Verification condition (VCC):
```sh
$ cbmc 09_abs.c –function abs –signed-overflow-check –show-vcc
```
Verify:
```sh
$ cbmc 09_abs.c –function abs –signed-overflow-check
```

### Uprošćavanje verifikacione formule

```sh
$ cbmc 10_escapefunction.c --function escape --pointer-check --bounds-check \
    --slice-formula --unwind 4
```

Opcija `–slice-formula` uklanja nepotrebne dodele, tj. dodele koje nisu
u vezi sa svojstvima koje proveravamo. Na taj način uprošćava formulu
koja se šalje SAT solveru i ubrzava proveru modela. Ispravimo
prijavljene greške i proverimo ponovo. Nije moguće rešiti problem što
`s` može biti bilo kakav pokazivač.

U programu `11_escapefunctionharness.c` imamo `main` funkciju koja će adekvatno pripremiti sve
argumente potrebne za funkciju `escape`.
```sh
$ cbmc 11_escapefunctionharness.c --pointer-check --bounds-check \
    --slice-formula --unwind 4
```

Probati sa različitim ograničenjem za odmotovanje. Uočiti greške i
ispraviti ih. Povećati dalje ograničenje u svrhu pretrage drugih grešaka
(`>20`).

### Binarna reprezentacija grafa kontrole toka

`goto-cc` je CBMC-ova zamena za kompajler i linker, (`goto-cl` verzija
za MS VisualStudio). Komandom
```sh
$ goto-cc 12_simple.c -o simple.goto
```
dobijamo binarnu reprezentaciju grafa kontrole toka.

Da nam generiše instrumentalizovan c kod, izvršavamo komandu:
```sh
$ goto-instrument --dump-c simple.goto out.c
```

`goto-instrument` čita binarno reprezentaciju grafa kontrole toka,
primenjuje odgovarajuću statičku analizu. kod je dopunjen proverama 
na mestu gde je uočena potencijalna greška. Zatim se
čuva dopunjena binarna reprezentacija. Komanda:
```sh
$ goto-instrument simple.goto --show-properties
```
daje sva uočena svojstva prilikom instrumentacije. Instrumentalizovan kod
analiziramo CBMC-om, izvršavanjem:
```sh
$ cbmc out.c
```
ili:
```sh
$ cbmc simple.goto
```


### Modelovanje problema

CBMC obezbeđuje primitive koje nisu pisane na jeziku C, a koje
modeluju nedeterminističke funkcije, tj. funkcije koje mogu uzastopno
vratiti mnogo različitih vrednosti. Upotreba:
```c
int nondeter_int();
```

deklariše nedeterminističku funkciju koja vraća podataka tipa `int`. 
Ovakve funkcije su dostupne za razne tipove. 
Nedeterminističke funkcije su korisne prilikom
modelovanja ulaznih podataka, nepoznatog okruženja, bibliotečkih
funkcija i praktično bilo čega što se može različito ponašati prilikom
izvršavanja u različitim okruženjima. Modelovanje korišćenjem
nedeterminističkim funkcijama je prilično zgodno, ali može se pokazati i
skupo. Sve moguće putanje izvršavanja moraju biti razmotane i istražene,
čak i one koje nisu moguće u praksi.

CBMC omogućava eksplicitno zadavanje korisnikovih preduslova i
postuslova i time omogućava da se analiza vrši po funkciji, čime se
značajno smanjuje opterećenje analizatora. Da bismo proverili da li
određeni poziv funkcije `foo` važi svojstvo `P`, delimo odlučivanje na
dva dela:
-   Pretpostavljajući da određeni predefinisani preduslov `C` važi u
    početnom stanju funkcije `foo`, i pretpostavljajući da svojstvo `P`
    važi na ulazu, da li svojstvo `P` važi i po izlasku iz funkcije?
-   Kad god je funkcija `foo` pozvana, da li garantovano važi preduslov
    `C` na ulazu?

Kada oba uslova važe, analiza će garantovano biti korektna. Na ovaj
način se proveravaju samo preduslovi i postuslovi, ali ne i
implementacija. Ovo olakšava testiranje, ali otvara prostor za sve
potencijalne greške programera. Ponekad ima smisla kombinovati ovaj sa
klasičnom analizom. Na primer, u nekom programu se nedeterminističke finkcije
koriste da modeluju sistemske pozive, dok se pretpostavke i garancije
važenja uslova koriste na bibiliotečkim funkcijama da bi osigurali
njihovo izvršavanje i u isto vreme svodeći analizu kôda na manje,
lokalne funkcije.

Tehnika postavljanja uslova i garancija važenja se postiže specifikacijom:
```c
__CPROVER_assert(uslov,poruka)
```

Ovo je osnovni oblik korisnički definisanih specifikacija podržanih od
strane CBMC. Kada se pokrene provera modela, proverava se važenja
uslova navedenog kao prvi argument na svim putanjama do definisane
granice. Ako granica nije data u komandnoj liniji, CBMC će kao i uvek
pokušati da pronađe gornju granicu dubine izvršavanja programa i
verifikovati ga nakon razmotavanja. Drugi argument je
niska za dijagnostikovanje, jer će biti prikazana u rezultatu analize
ako CBMC pronađe kontraprimer za uslov.

Pretpostavke okruženja se zadaju specifikacijom:
```c
__CPROVER_assume(uslov)
```

CBMC interpretira ovaj poziv malo drugačije od prethodnog. Bilo koja
putanja koja ne zadovoljava uslov naveden kao argument, biće odbačena iz
analize. Čak šta više, ako takva putanja negde kasnije i sadrži neku
grešku, ona neće biti prijavljena u rezultatu. Ovo je korisno u
slučajevima modelovanja okruženja, ukoliko verujemo da će argumenti
prosleđeni funkciji uvek zadovaljavati navedene uslove. Ove dve
specifikacije, zajedno sa nedeterminističkim funkcijama i, naravno,
programiranjem omogućavaju modelovanje zanimljivih tvrđenja.

U primeru `05_assume.c`, ne postoji izračunavanje za koje ovo prolazi može da bude ispunjen
uslov iz `if ( x>0 )` i pretpostavka iz `__CPROVER_assume (x < 0)` Zbog
svojstva `__CPROVER_assume` sve grane stabla izvrsavanja od te
pretpostavke koje ne zadovoljavaju uslov biće odbačene i iz tog razloga
nam neće prijaviti grešku, sta god uslov bio.
 

U primeru `06_postcondition.c`, CBMC ne prijavljuje grešku iako za 
`N = -1` i `x = 0` ne bi važio uslov.
To se događa jer `N` i `x` nisu inicijalizovane i CBMC pretpostavlja
da su im vrednosti `0`. Da bismo uklonili tu pretpostavku moramo dodati
nedeterminstičke vrednosti za `N` i `x`.


### Višenitni programi

U primeru `10_increment.c`, kontraprimer koji nam CBMC prijavljuje nam govori da je `x` dva puta
postavljeno na 1. Problem je u pristupu kritičnoj sekciji od strane obe
niti. Ograđivanjem kritične sekcije `mutex`-om rešavamo taj problem.

U primeru `11_incrementLoop.c` je problem što imamo petlju u kojoj se čita vrednost deljene
promenljive i potom ažurira. CBMC ne uspeva da odredi sam gornju
granicu razmotavanja petlji pa je neophodno da je zadamo.

U primeru `12_mutex.c` postoje 3 niti, jedna glavna u kojoj se izvršava `main`
funkcija, jedna koja je proizvođač (engl. *producer*) i jedna koja je
potrošač (engl. *consumer*). Kako se program izvrašava, instrukcije koje
niti izvršavaju mogu se učešljati i bilo kom mogućem redosledu jer je
raspoređivanje prepušteno opreativnom sistemu. CBMC ovakave situacije
modelira razmotavanjem kôda izvršenog od strane svake niti u svim
mogućim poretcima, tretirajući izbor rasporeda nedeterminističkim. Svaka
nit ima svoj lokalni stek okvir, i one su dostupne samo odgovarajućoj
niti. Dok globalne su dostupne svim nitima. Naravno, problem nastaje
kada više niti pristupa deljenim podacima.

U ovom kodu `producer` i `consumer` pokušavaju da postignu međusobno
isključenje preko 3 globalne promenljive: `try_producer`, `try_consumer`
i `turn`. Kada bilo koja osim glavne niti želi pristupi kritičnoj
sekciji ona signalizira svoju nameru postavljajući promenljivu
`try_producer`, odnosno `try_consumer`, na 1. Potom daje priliku drugoj
niti da uđe u kritičnu sekciju, prostavljajući promenljivu `turn` na
vrednost koja odgovora drugoj niti i čekajući u `while` petljama. Kada
nit uđe u kritičnu sekciju ona obavi svoj posao nad deljenim podacima i
vraća vrednost promenljive `try_producer`, odnosno `try_consumer`, na 0.

Prvo ćemo ispraviti greške vezane za memoriju. Neki problemi sa
memorijom mogu biti izazvani prilikom pristupanja deljenim podacima i
ako međusobno isključenje dve niti nije ispunjeno.

CBMC ne može naći gornju granicu razmotavanja petlji, naročito što
imamo petlje u kojima niti čekaju na ulazak u kritičnu sekciju.
```sh
$ cbmc 12_mutex.c --unwind 7 --no-unwinding-assertions \
    --slice-formula --bounds-check --pointer-check
```

Pronalazi nam kontraprimer u kom se vidi da nit koja odgovara funkciji
`consumer` ulazi prva u kritičnu sekciju i svojom akcijom smanjuje
`num_waiting` na -1, a potom se poziva funkcija `process` da ispise
element na tom indeksu.

Ponavljamo prethodni poziv i iz podužeg kontraprimera zaključujemo da u
poslednjoj liniji funkcije `next_data` vraćamo ne vrednost koju smo
upisali u niz već narednu. Popravljamo da se vrati vrednost na indeksu
`data_pos-1`.

Opcija komandne linije `–unwind 7` utiče na međusobno isključenje niti,
jer nam utiče na petlju u kojoj se čeka na dozvolu za ulazak u kritičnu
sekciju. Petlja se izvršava kao da smo dodali `break` nakon 6.
iteracije. Zbog toga nam se mogu dogoditi nejasne greške da na primer
`num_waiting` bude smanjen na 0 u niti `consumer`, a potom vraćena na 2
u niti `producer`, što se ne bi smelo dogoditi. =1

Uveriti se da i `producer` i `consumer` nit završavaju i da su svi
podaci iz `data_source` obrađeni od strane niti `consumer`. Biće
potrebno modifikovati kod da bi se ovo ostvarilo. Savet je da se koriste
CBMC-ove korisničke specifikacije.

