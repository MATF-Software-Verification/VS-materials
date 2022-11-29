## KLEE heuristike

KLEE je primenjen na svih 89 programa u verziji 6.10 paketa GNU 
Coreutils, koji obuhvata oko 80,000 linija koda biblioteka i 61,000
linija iz konkretnih programa. Ti programi interaguju sa okruženjem da
bi omogućili različite funkcionalnosti, kao što je manipulisanje fajl
sistemom (npr. `ls`, `dd`, `chmod`), prikazivanje i
konfigurisanje svojstava sistema (npr. `hostname`, `logname`, `printenv`),
kontrolu poziva komandi (npr. `nohup`, `nice`, `env`), obrada tekstualnih
datoteka (npr. `sort`, `od`, `patch`), itd.

Svaki program iz paketa Coreutils dolazi sa velikim skupom ručno
pisanih testova, koji se proširuje sa svakom novo otkrivenom greškom ili
dodatom opcijom. KLEE je nadmašio ručno pisani skup testova u pogledu
ukupne pokrivenosti linija (84.5% nasuprot 67.7%) i prosečne pokrivenosti po
alatu (90.9% nasuprot 68.4%). Postigao je 100% pokrivenost na 16 programa i
preko 90% na 56 programa dok ručno pisani testovi imaju 100% pokrivenost
samo na jednom programu (`true`) i preko 90% samo na 7 programa. U
suštini, za 89h, tj. 1h po programu, KLEE je za 16.8% premašio
pokrivenost skupa ručno pisanih testova u periodu od 15 godina.

KLEE je pronašao 10 grešaka u Coreutils (uglavnom grešaka sa
memorijom). U tabeli ispod je dat spisak poziva koje je KLEE
generisao za pronađene greške. Prve tri greške postoje bar od 1992.
godine, dok su ostale novije. U trenutku objavljivanja rezultata 
greška za `seq` je već bila ispravljena u neobjavljenoj verziji, a
ostale greške su potvrđene i ispravljene u toku od 2 dana od
prijavljivanja. Dodatno, od tada se u zvaničnom skupu testova nalaze i
KLEE-om generisani testovi za ove greške.

```txt
paste -d\\ abcdefghijklmnopqrstuvwxyz
pr -e t2.txt
tac -r t3.txt t3.txt
mkdir -Z a b
mkfifo -Z a b
mknod -Z a b p
md5sum -c t1.txt
ptx -F abcdefghijklmnopqrstuvwxyz
ptx x t4.txt
seq -f %0 1
```
```txt
t1.txt: "\t \tMD5("
t2.txt: "\b\b\b\b\b\b\b\t"
t3.txt: "\n"
t4.txt: "a"
```

### Korišćenje različitih heuristika za pretragu

KLEE koristi sledeće heuristike za pretragu putanja:
-   Depth-First Search (DFS)
-   Random State Search
-   Random Path Selection
-   Non Uniform Random Search (NURS)

Heuristika se može izabrati KLEE-ovom opcijom `-search`, npr.
`-search=dfs`. Za *NURS* se mora dodati opcija za heuristiku kojom se
dodeljuju težine pojedinim putanjama i tako odlučuje koja će biti
naredna praćena:
- `nurs:covnew`: koristi *Coverage-New* heuristiku kojom se daje veća težina putanji koja će pokriti nepokriven deo koda;
- `nurs:md2u`: koristi *Min-Dist-to-Uncovered* heuristiku kojom se bira putanja najbliža nepokrivenoj instrukciji;
- `nurs:depth`: koristi *`2^{depth}`* heuristiku
- `nurs:icnt`: koristi *Instr-Count* heuristiku
- `nurs:cpicnt`: koristi *CallPath-Instr-Count* heuristiku
- `nurs:qc`: koristi *Query-Cost* heuristiku

KLEE-u se može zadati da koristi više heuristika na *round-robin*
način, da bi se sprečilo da pojedine heuristike zaglave u lokalnom
maksimumu.

Podrazumevana je *random-path* ukomponovan sa `nurs:covnew`.

Moguće zadati željenu heuristiku korišćenjem opcije `–search`.
Detaljnije informacije u vezi sa parametrima za ovu opciju možete dobiti
pozivom KLEE-a sa opcijom `–help`.


### Testiranje heuristika

Testiraćemo izbor putanja različitih heuristika na primerima koji imaju `N` simboličkih promenljivih i za svaku od njih imamo `if-else` grane. Nakon tih provera imamo i računanje količnika. Zbog toga što je nedozvoljeno deliti nulom, KLEE implicitno za tu naredbu dodaje proveru. Takvo ponašanje se javlja kod svih kritičnih mesta u kôdu. Za svaki broj simboličkih promenljivih imamo 3 verzije programa. Verzije sa sufiksom `-1.c` i `-2.c` imaju deljenje nulom samo na različitim putanjama, dok verzija sa sufiksom `-v.c` nema spornu putanju.

Ukoliko želimo da vidimo za svaki generisani test primer putanju i upit
koji je slan solveru, prilikom poziva KLEE-a treba zadati opcije
`–write-paths`.

Za potrebe testiranja dodaćemo i opciju `-exit-on-error` da se prekine
sa simboličkim izvršavanjem čim se dođe do sporne putanje.

Merenje je automatizovano skriptom `measure_time.sh`.

Pokrećemo sa `./measure_time.sh dfs yes 15` da se dfs heuristika koristi
za izbor putanje, da nam se generišu sve putanje i upiti za solver i da
ne pokrećemo programe sa više od 15 simboličkih promenljivih.

Za verzije `*-1.c`, ako se koristi `–search=dfs` opcija, odmah se
nailazi na spornu putanju. Stoga se test primer za nju generiše uvek kao
`test1`. Nije ni potrebno čekati kraj cele pretrage jer odmah izbaci
grešku.

Za verzije `*-2.c`, ako se koristi `–search=dfs` opcija, sporna putanja
je poslednja koja se obilazi. Do nje neće doći mnogo brzo, vreme zavisi
od broja putanja koje joj prethode.

Sa `–search=random_path` opcijom primenjenom na programe sa većim brojem
promenljivih, čak i ne pronađe spornu putanju. Uzrok je vrlo razgranato
stablo izvršavanja, tj. veliki broj putanja.

Ukoliko otvorimo generisanu datoteku sa izveštajem `report_dfs.txt`
videćemo da su verzije `*-1.c` uvek ranije dolazile do greške i
prekidale dalje simboličko izvršavanje. U odgovarajućem direktorijumu
naći ćemo testove. Za test1 nas interesuje putanja. Primećujemo da je
uvek birana `else` grana i da smo tako odmah došli do sporne putanje.
Verzija `*-2.c` je tako napisana da `dfs` heuristikom tek na kraju
obilazimo spornu putanju. Kod složenijih stabala izvršavanja, tj. kod
programa sa većim brojem simboličkih promenljivih može se dogoditi i da
je ne pronađe pre nego što potroši resurse.

Ako imamo `N` promenljivih i za svaku od njih po grananje imamo $2^N$
putanja. Verovatnoća da heuristika `random-path` ubode spornu putanju je
`1/{2^N}`. To se može dogoditi ranije ili kasnije, ali se može desiti da
se i ne isprati ta putanja pre prekoračenja memorijskog prostora, zbog
prevelike razgranatosti stabla.

Problem sa memorijom nastaje jer je KLEE u suštini program koji se
izvršava u okviru jednog procesa i ceo stablo mora biti u svakom
trenutku u memoriji. Očekivano, bolje se performanse u postižu
paralelizacijom. *Cloud9* je program koji dinamički distribuira delove
stabla između POSIX niti koje izvršavaju simboličko izvršavanje programa
bazirano na KLEE-u. Time postiže i bolja pokrivenosti i za kraće
vreme.

Ipak, ukoliko se iskoristi KLEE-ova opcija `-optimize` primenjuju se
optimizacije kompajlera i izvršavanje je višestruko brže. Samim tim
pronalaze se sporne putanje i na programima sa vrlo razgranatim stablom.


### Kreiranje nove heuristike za KLEE

Kôd vezan za heuristike u KLEE-u se nalazi u datotekama
` /build/klee/lib/Core/Searcher.h` i
` /build/klee/lib/Core/Searcher.cpp`. Nova heuristika treba da bude
pisana u klasi koja će naslediti klasu `Searcher`. Kôd nove heuristike
uneti u pomenute datoteke. Navesti ime nove heuristike u
`CoreSearchType` i dopuniti metode klase `UserSearcher` sa informacijama
o novoj heuristici. Klasa `Executor` svojom metodom `run` kreira stablo
izvrašavanja, kreira objekat klase `UserSearcher` i prati i izvršava
stanja programa, tj. objekata klase `ExecutionState`.

Nakon izmena koda bilo potrebno i ponovo izgraditi KLEE. Zato se treba
pozicionirati u KLEE-ov direktorijum.
```sh
$ cd /klee/dir 
$ LLVM_VERSION=6.0 SANITIZER_BUILD= BASE="/libc++/path/" \
    ./scripts/build/build.sh libcxx
$ mkdir build
$ cd build
$ cmake \
    -DENABLE_SOLVER_STP=ON \
    -DENABLE_SOLVER_Z3=ON  \
    -DENABLE_POSIX_RUNTIME=ON \
    -DENABLE_KLEE_UCLIBC=ON \
    -DKLEE_UCLIBC_PATH="/klee-uclibc/path/" \
    -DUSE_CMAKE_FIND_PACKAGE_LLVM=OFF  \
    -DLLVM_CONFIG_BINARY="/bin/llvm-config" \
    -DLLVMCC="/bin/clang" \
    -DLLVMCXX="/bin/clang++" \
    -DENABLE_DOCS=ON \
    -DENABLE_DOXYGEN=ON \
    -DENABLE_KLEE_LIBCXX=ON \
    -DLIT_ARGS="-v" \
    -DLIT_TOOL="/usr/bin/"   \
    -DENABLE_UNIT_TESTS=OFF \
    -DENABLE_SYSTEM_TESTS=ON \
    -DCMAKE_BUILD_TYPE="Debug" \
    ../

$ make   
$ sudo make install
```

