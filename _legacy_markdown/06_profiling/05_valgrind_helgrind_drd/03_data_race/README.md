#### Trka za podacima

Trka za podacima *(eng. Data race)* može da se javi usled nedostatka
adekvatnog zaključavanja ili sinhronizacije. Pristup podacima bez
adekvatnog zaključavanja ili sinhronizacije se odnosi na problem kada
dve ili više niti pristupaju deljenom podatku bez sinhronizacije. Na
ovaj način je moguće da dve ili više niti u istom trenutku pristupe
deljenom objektu.

Algoritam detekcije pristupa promenljivoj bez sinhronizacije u okviru
alata *Helgrind* implementira *„desilo se pre"* relaciju *(eng.
„happens-before" relation)*. Na primer, kao u gore pokazanom programu,
nit roditelj kreira nit dete. Zatim obe menjaju vrednost promenljive
`var`, a zatim nit roditelja čeka da nit deteta izvrši svoju funkciju.
Ovaj program nije dobro napisan jer ne možemo sa sigurnošću da znamo
koja je vrednost promenljive `var` prilikom štampanja iste. Ako je nit
roditelja brža od niti deteta, onda će biti štampana vrednost 10, u
suprotnom će biti 20. Brzina izvršavanja niti roditelja i deteta je
nešto na šta programer nema uticaja. Rešenje ovog problema je u
zaključavanju promenljive `var`. Na primer, možemo da pošaljemo poruku
iz niti roditelj nakon što ona promeni vrednost promenljive `var`, a nit
dete neće promeniti vrednost promenljive `var` dok ne dobije poruku. Na
ovaj način smo sigurni da će program ispisati vrednost 10. Razmena
poruka kreira *„desilo se pre"* zavisnost između dve dodele vrednost:
`var = 20;` se događa pre `var = 10;`. Takođe, sada više nemamo pristup
promenljivoj bez sinhronizacije. Nije obavezno da šaljemo poruku iz niti
roditelj. Možemo poslati poruku iz niti dete nakon što ona izvrši svoju
dodelu. Na ovaj način smo sigurni da će se ispisati vrednost 20.

Alat *Helgrind* radi na istom ovom principu. On prati svaki pristup
memorijskoj lokaciji. Ako se lokacija, u ovom primeru `var`, pristupa iz
dve niti, Helgrind proverava da li su ti pristupi povezani sa *„desilo
se pre"* vezom. Ako nisu, alat prijavljuje grešku o pristupu
promenljivoj bez sinhronizacije. Ako je pristup deljenoj promenljivoj iz
dve ili više programerske niti povezan sa *„desilo se pre"* relacijom,
znači da postoji sinhronizacioni lanac između programskih niti koje
obezbeđuje da se sam pristup odvija po tačno određenom redosledu, bez
obzira na stvarne stope napretka pojedinačnih niti.

Standardne primitive `pthread` niti kreiraju *„desilo se pre"* relaciju:

-   Ako je muteks otključan od strane niti `T1` , a kasnije ili odmah
    zaključan od strane niti `T2` , onda se sav pristup memoriji iz niti
    `T1` pre otključavanja muteksa dešava pre nego onih pristupa iz niti
    `T2` nakon njenog zaključavanja muteksa.

-   Ista ideja se odnosi i na `reader-writer` zaključavanje
    promenljivih.

-   Ako je kondiciona promenljiva signalizirana u funkciji niti `T1` i
    ako druga nit `T2` čeka na taj signal, da bi nastavila sa radom,
    onda se memorijski pristup u `T1` dešava pre signalizacije, dok nit
    `T2` vrši pristup memoriji nakon što izađe iz stanja čekanja na
    signal koji šalje nit `T1`.

-   Ako nit `T2` nastavlja sa izvršavanjem nakon što nit `T1` oslobodi
    semafor, onda kažemo da postoji *„desilo se pre"* relacija između
    programskih niti `T1` i `T2`.

*Helgrind* presreće sve gore navedene događaje i kreira graf koji
predstavlja sve *„desilo se pre"* relacije u programu. Takođe, on prati
sve pristupe memoriji u programu. Ako postoji pristup nekoj memorijskoj
lokaciji u programu od strane dve niti i *Helgrind* ne može da nađe
putanju kroz graf od jednog pristupa do drugog, generiše podatak o
grešci u programu koji analizira. *Helgrind* ne proverava da li postoji
pristup memorijskoj lokaciji bez sinhronizacije ukoliko se svi pristupi
toj lokaciji odnose na čitanje sadržaja te lokacije. Dva pristupa
memorijskoj lokaciji su u *„desilo se pre"* relaciji, i ako postoji
proizvoljno dugačak lanac sinhronizacije događaja između ta dva
pristupa. Ako nit `T1` pristupa lokaciji `M`, zatim signalizira nit `T2`
, koja kasnije signalizira nit `T3` koja pristupa lokaciji `M`, kažemo
da su ova dva pristupa između niti `T1` i `T3` u *„desilo se pre"*
relaciji, iako između njih ne postoji direktna veza.

Pokrenimo Helgrind:
```txt
==972== Thread #1 is the program's root thread
==972==
==972== ---Thread-Announcement------------------------------------------
==972==
==972== Thread #2 was created
==972==    at 0x51643DE: clone (clone.S:74)
==972==    by 0x4E46149: create_thread (createthread.c:102)
==972==    by 0x4E47E83: pthread_create@@GLIBC_2.2.5 (pthread_create.c:679)
==972==    by 0x4C34BB7: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==972==    by 0x400705: main (simpleDataRace.c:12)
==972==
==972== ----------------------------------------------------------------
==972==
==972== Possible data race during read of size 4 at 0x60104C by thread #1
==972== Locks held: none
==972==    at 0x400706: main (simpleDataRace.c:13)
==972==
==972== This conflicts with a previous write of size 4 by thread #2
==972== Locks held: none
==972==    at 0x4006C7: child_fn (simpleDataRace.c:6)
==972==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==972==    by 0x4E476B9: start_thread (pthread_create.c:333)
==972==  Location 0x60104c is 0 bytes inside global var "var"
==972==  declared at simpleDataRace.c:3
==972==
--972-- warning: evaluate_Dwarf3_Expr: unhandled DW_OP_ 0xf2
==972== ----------------------------------------------------------------
==972==
==972== Possible data race during write of size 4 at 0x60104C by thread #1
==972== Locks held: none
==972==    at 0x40070F: main (simpleDataRace.c:13)
==972==
==972== This conflicts with a previous write of size 4 by thread #2
==972== Locks held: none
==972==    at 0x4006C7: child_fn (simpleDataRace.c:6)
==972==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==972==    by 0x4E476B9: start_thread (pthread_create.c:333)
==972==  Location 0x60104c is 0 bytes inside global var "var"
==972==  declared at simpleDataRace.c:3
```

*Helgrind* algoritam za detekciju pristupa memoriji bez sinhronizacije
od prikupljeni informacija  najpre ispisuje podatke gde su niti koje
uzrokuju grešku napravljene. Glavni podatak o grešci počinje sa
*„Possible data race during read"*. Zatim se ispisuje adresa gde se
nesinhronizovan pristup memoriji dešava, kao i veličina memorije kojoj
se pristupa. Prikazuje stek za obe niti, nit roditelja i nit deteta. U
nastavku Helgrind ispisuje gde druga nit pristupa istoj lokaciji. Na
kraju, *Helgrind* pokrenut sa opcijom `–read-var-info=yes` ispisuje i
samo ime promenljive kojoj se pristupa, kao i gde u programu je ta
promenljiva deklarisana. Na obe lokacija pristupa promenljivoj
*Helgrind* ispisuje i sva zaključavanja koja postoje u tom trenutku, ali
ovde ih nema ni na jednom mestu. Takva informacija je uglavnom korisna
da se zaključi koja nit nije uspela da zaključa željeni objekat.\
Kad imamo 2 poziva na steku kako naći uzrok trke za podacima?\
Kao prvo, ispitati lokacije na koje se referiše u svakom steku. Trebalo
bi da oba pokazuju na pristup istoj lokaciji, tj. promenljivoj. Potom
treba utvrditi kako tu lokaciju obezbediti. Ukoliko je već bilo
planirano da bude zaštićena muteksom, treba zaključati i otključati
muteks na obe tačke pristupa, čak i ako je na jednom mestu planirano
samo čitanje. *Helgrind* u momentu pristupa ispisuje i sve katance koje
u tom trenutku drži nit koja pristupa lokaciji. Ukoliko smo zaboravili
da zaključamo, tako možemo primetiti.

Možda je namera bila da se lokacija nekim drugim postupkom obezbedi,
signalizacijom uslovnih promenljivih, npr. U tom slučaju treba pokušati
da se pronađe dokaz da se raniji pristup u relaciji *„desilo se pre"* sa
kasnijim pristupom. Činjenica je da *Helgrind* prijavljuje problem sa
trkom za podacima ako nije uočio *„desilo se pre"* relaciju između dva
pristupa. Ukoliko je u pravu, onda ni mi ne bi trebalo da možemo da
nađemo takvu relaciju ni sa detaljnim ispitivanjem izvornog kôda.
Ispitivanjem kôda ćemo uočiti i gde bi operacije za sinhronizaciju
trebalo da stoje.\
*DRD* ispisuje poruku svaki put kada otkrije da je došlo do trke za
podacima u programu. Treba imati u vidu par sledećih stvari prilikom
tumačenja ispisa koji nam alat *DRD* daje. Prvo, *DRD* dodeljuje svakoj
niti jedinstveni broj `ID`. Brojevi koji se dodeljuju nitima kreću od
jedan i nikada se ne koristi isti broj za više niti. Drugo, termin
segment se odnosi na sekvencu uzastopnih operacija čuvanja, čitanja i
sinhronizacije koje se izvršavaju u jednoj niti. Segment uvek počinje i
završava se operacijom sinhronizacije. Analiza trke za podacima se
izvršava između dva segmenta umesto između pojedinačnih operacija
čitanja i čuvanja podataka, isključivo zbog učinka. Na kraju, uvek
postoje bar dva pristupa memoriji prilikom trke za podacima. *DRD*
štampa izveštaj o svakom pristupu memoriji koje je dovelo do trke za
podacima.

Pokrenućemo za prethodni primer sada alat *DRD*:
```txt
==24411== Conflicting load by thread 1 at 0x0060104c size 4
==24411==    at 0x400706: main (simpleDataRace.c:13)
==24411== Allocation context: BSS section of /home/student/vs/06/helgrind/a.out
==24411== Other segment start (thread 2)
==24411==    at 0x51703E1: clone (clone.S:81)
==24411== Other segment end (thread 2)
==24411==    at 0x516A807: madvise (syscall-template.S:84)
==24411==    by 0x4E5394C: start_thread (pthread_create.c:432)
==24411==
==24411== Conflicting store by thread 1 at 0x0060104c size 4
==24411==    at 0x40070F: main (simpleDataRace.c:13)
==24411== Allocation context: BSS section of /home/student/vs/06/helgrind/a.out
==24411== Other segment start (thread 2)
==24411==    at 0x51703E1: clone (clone.S:81)
==24411== Other segment end (thread 2)
==24411==    at 0x516A807: madvise (syscall-template.S:84)
==24411==    by 0x4E5394C: start_thread (pthread_create.c:432)
```

Pristupi memoriji koji učestvuju u trci za podacima su označeni kao
*konfliktni* sa prethodnim pristupom. Mora ih biti bar dva od koji je
bar jedan sa namerom za menjanje podatka na memorijskoj lokaciji. Za
jedan od pristupa se prikazuje potpun stek poziva, a za ostale delimični
stek pozivi. Oni uglavnom uključuju početak i kraj segmenta pristupa.
Ove informacije se mogu protumačiti na sledeći način:

-   Krenuti od dna oba steka poziva, brojati stek okvire sa istim
    imenima funkcije, izvorne datoteke i broja linije.

-   Naredni viši okvir na steku u oba steka poziva govori između kojih
    delova izvornog kôda se desio pristup memorijskoj lokaciji.

Problem u ovom primeru je što nemamo sinhronizaciju pristupa
promenljivoj `var`. Uvođenjem muteksa i zaključavanjem istog prilikom
pristupa promenljivoj, će rešiti problem.
