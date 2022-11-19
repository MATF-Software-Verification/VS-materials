### Helgrind / DRD

Helgrind je alat u sklopu programskog paketa Valgrind koji otkriva
greške sinhronizacije prilikom upotrebe modela niti `POSIX`.

Glavne apstrakcije modela `POSIX` niti su: grupa niti koji deli
zajednički adresni prostor, formiranje niti, čekanje na završetak
izvršavanja funkcije niti, izlaz iz funkcije niti, muteks objekti,
uslovne promenljive, čitaj-piši zaključavanje i semafori.

Problemi poput ovih imaju kao rezultat nereproduktivne, vremenski
zavisne padove, mrtve petlje i druga loša ponašanja programa koja se
mogu teško otkriti drugim sredstvima. *Helgrind* je svestan svih
apstrakcija niti i prati njihove efekte. Najbolje radi ukoliko program
koristi isključivo `POSIX` niti. Moguće ga je koristiti i za programe
koji koriste druge standarde za niti, ali je neophodno opisati
*Helgrind*-u njihovo ponašanje korišćenjem `ANNOTATE_*` makroa
definisanih u `helgrind.h` zaglavlju).

*DRD* je *Valgrind*-ov alat za detekciju grešaka u *C* i *C++*
programima koji koriste više niti. Alat radi za svaki program koji
koristi niti POSIX standarda ili koji koriste koncepte koji su
nadograđeni na ovaj standard.

|                              | Helgrind | DRD |
|------------------------------|----------|-----|
| Mrtve petlje                 | DA       | NE  |
| Trka za podacima             | DA       | DA  |
| Nepravilno korišćenje API-ja | DA       | DA  |
| Zadržavanje podataka         | NE       | DA  |

Alati *DRD* i *Helgrind* ne koriste iste algoritme za otkrivanje
grešaka, samim tim ne otkrivaju iste tipove grešaka, iako imaju veliki
broj poklapanja. Helgrind proizvodi izlaze koji su lakši za
interpretaciju, dok *DRD* ima bolje performanse.

