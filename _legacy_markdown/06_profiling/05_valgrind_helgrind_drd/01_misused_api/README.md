#### Loša upotreba intefejsa za programiranje `POSIX` niti

Mnoge implementacije interfejsa su optimizovane radi kraćeg vremena
izvršavanja. Takve implementacije se neće buniti na određene greške (ako
muteks otključa neka druga nit, a ne ona koja ga je zaključala).

Greške koje Helgrind i DRD pronalaze su:

-   Greške u otključavanju muteksa - kada je muteks nevažeći, nije
    zaključan ili je zaključan od strane druge niti;

-   Greške u radu sa zaključanim muteksom - uništavanje nevažećeg ili
    zaključanog muteksa, rekurzivno zaključavanje nerekurzivnog muteksa,
    dealokacija memorije koja sadrži zaključan muteks;

-   Prosleđivanje muteksa kao argumenta funkcije koja očekuje kao
    argument `reader-writer lock` i obrnuto;

-   Greške sa `pthread barrier` - nevažeća ili dupla inicijalizacija,
    uništavanje `pthread barrier` koji nikada nije inicijalizovan ili
    koga niti čekaju ili čekanje na objekat koji nije nikada
    inicijalizovan;

-   Greške prilikom korišćenja funkcije `pthread_cond_wait` -
    prosleđivanje nezaključanog, nevažećeg ili muteksa koga je
    zaključala druga nit;

-   `Pthread` funkcija vrati kôd greške koji je potrebno dodatno
    obraditi;

-   Greška kada se nit uništi, a još drži zaključanu promenljivu;

-   Nekonzistentne veze između uslovnih promenljivih i njihovih
    odgovarajućih muteksa.

Ovakve greške mogu da dovedu do nedefinisanog ponašanja programa i do
pojave grešaka u programima koje je kasnije veoma teško otkriti.
*Helgrind* presreće pozive ka funkcijama biblioteke `pthread`, i zbog
toga je u mogućnosti da otkrije veliki broj grešaka. Za sve `pthread`
funkcije koje *Helgrind* presreće, generiše se podatak o grešci ako
funkcija vrati kôd greške, iako *Helgrind* nije našao greške u kôdu.
Provere koje se odnose na mutekse se takođe primenjuju i na
`reader-writer lock`. Prijavljena greška prikazuje i primarno stanje
steka koje pokazuje gde je detektovana greška. Takođe, ukoliko je moguće
ispisuje se i broj linije u samom kôdu gde se greška nalazi. Ukoliko se
greška odnosi na muteks, *Helgrind* će prikazati i gde je prvi put
detektovao problematični muteks.

Primer `01_bad.unlock.c` prikazuje ovakav tip grešaka. Prevodimo program sa opcijom `-pthread` pošto koristimo POSIX niti i pokrećemo Helgrind:
```sh
$ valgrind –tool=helgrind -v –log-file=bl.log ./bad_unlock.out
```
Opcijom `–log-file=bl.log` zadajemo da nam se izveštaj upiše u datoteku `bl.log`. Vidimo da nam je prijavljen veliki broj grešaka:

```txt
==24477== ---Thread-Announcement------------------------------------------
==24477==
==24477== Thread #1 is the program's root thread
==24477==
==24477== ----------------------------------------------------------------
==24477==
==24477== Thread #1 unlocked a not-locked lock at 0xFFEFFF720
==24477==    at 0x4C326B4: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x4008DE: nearly_main (01_bad_unlock.c:27)
==24477==    by 0x40096D: main (01_bad_unlock.c:49)
==24477==  Lock at 0xFFEFFF720 was first observed
==24477==    at 0x4C360BA: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x4008B1: nearly_main (01_bad_unlock.c:23)
==24477==    by 0x40096D: main (01_bad_unlock.c:49)
==24477==  Location 0xffefff720 is 0 bytes inside local var "mx1"
==24477==  declared at 01_bad_unlock.c:18, in frame #1 of thread 1
```

Prijavljena nam je greška u da imamo u 27. liniji otključavanje
nezaključanog muteksa. Poruka *was first observed* nam dodatno
objašnjava gde je taj muteks prvi put primećen od strane *Helgrind*-a.

```txt
==24477== Thread #2 unlocked lock at 0xFFEFFF750 currently held by thread #1
==24477==    at 0x4C326B4: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x40084D: child_fn (01_bad_unlock.c:11)
==24477==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x4E476B9: start_thread (pthread_create.c:333)
==24477==  Lock at 0xFFEFFF750 was first observed
==24477==    at 0x4C360BA: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x4008F2: nearly_main (01_bad_unlock.c:31)
==24477==    by 0x40096D: main (01_bad_unlock.c:49)
==24477==  Location 0xffefff750 is 0 bytes inside local var "mx2"
==24477==  declared at 01_bad_unlock.c:18, in frame #2 of thread 1
```

Prijavljen nam je pokušaj da nit koja nije zaključala muteks pokušava da
ga otključa naredbom u liniji 11.

```txt
==24477== Thread #1 unlocked an invalid lock at 0xFFEFFF848
==24477==    at 0x4C326B4: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x40094D: nearly_main (01_bad_unlock.c:41)
==24477==    by 0x40096D: main (01_bad_unlock.c:49)
==24477==
==24477== ----------------------------------------------------------------
==24477==
==24477== Thread #1's call to pthread_mutex_unlock failed
==24477==    with error code 22 (EINVAL: Invalid argument)
==24477==    at 0x4C327DA: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x40094D: nearly_main (01_bad_unlock.c:41)
==24477==    by 0x40096D: main (01_bad_unlock.c:49)
```

Greška je u pokušaju otključavanja promenljive koja nije muteks.

```txt
==24477== Thread #1 unlocked a not-locked lock at 0xFFEFFF720
==24477==    at 0x4C326B4: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x4008DE: nearly_main (01_bad_unlock.c:27)
==24477==    by 0x400990: main (01_bad_unlock.c:50)
==24477==  Lock at 0xFFEFFF720 was first observed
==24477==    at 0x4C360BA: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x4008B1: nearly_main (01_bad_unlock.c:23)
==24477==    by 0x40096D: main (01_bad_unlock.c:49)
==24477==  Location 0xffefff720 is 0 bytes inside local var "mx1"
==24477==  declared at 01_bad_unlock.c:18, in frame #1 of thread 1
```

Greška je u tome što se u liniji 27 otključava već otključani muteks.

```txt
==24477== Thread #1: Attempt to re-lock a non-recursive lock I already hold
==24477==    at 0x4C320F4: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x400901: nearly_main (01_bad_unlock.c:32)
==24477==    by 0x400990: main (01_bad_unlock.c:50)
==24477==  Lock was previously acquired
==24477==    at 0x4C321BC: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==24477==    by 0x400901: nearly_main (01_bad_unlock.c:32)
==24477==    by 0x40096D: main (01_bad_unlock.c:49)
```

Prijavljuje nam da ponovno zaključavamo muteks koji je nit već ranije
zaključala u liniji 32 funkcije `nearly_main` iz 49. linije `main` fje.
Ponovno zaključavanje je nastalo u u liniji 32 funkcije  `nearly_main`
iz 50. linije `main` funkcije, jer se tada ponovo poziva funkcija
`nearly_main`. Problematični muteks je ostao zaključan iz prethodnog
izvšavanja funkcije. Ako na kraju funkcije otključamo muteks `mx2`, rešićemo i ovaj i naredni problem.

```txt
==24477== Thread #1: Exiting thread still holds 1 lock
==24477==    at 0x5129748: _Exit (_exit.c:31)
==24477==    by 0x5096FAA: __run_exit_handlers (exit.c:97)
==24477==    by 0x5097044: exit (exit.c:104)
==24477==    by 0x507D836: (below main) (libc-start.c:325)
```

Greška je što nit završava sa radom, ali nije otključala sve katance
koje je držala.

Ispravimo greške jednu po jednu sve dok nam *Helgrind* prijavljuje
nešto. Sada pokrećemo program kroz *Valgrind* sa alatom *drd*.

```sh
$ valgrind --tool=drd ./bad_unlock.out
```

```txt
==8394== drd, a thread error detector
==8394== Copyright (C) 2006-2015, and GNU GPL'd, by Bart Van Assche.
==8394== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==8394== Command: ./bad_unlock.out
==8394==
---------------------
==8394== Mutex reinitialization: mutex 0xffefff570, recursion count 0, owner 1.
==8394==    at 0x4C36719: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==8394==    by 0x4008A1: nearly_main (01_bad_unlock_fixed.c:23)
==8394==    by 0x40096B: main (01_bad_unlock_fixed.c:51)
==8394== mutex 0xffefff570 was first observed at:
==8394==    at 0x4C36719: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==8394==    by 0x4008A1: nearly_main (01_bad_unlock_fixed.c:23)
==8394==    by 0x400948: main (01_bad_unlock_fixed.c:50)
==8394==
==8394== Mutex reinitialization: mutex 0xffefff5a0, recursion count 0, owner 1.
==8394==    at 0x4C36719: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==8394==    by 0x4008D3: nearly_main (01_bad_unlock_fixed.c:31)
==8394==    by 0x40096B: main (01_bad_unlock_fixed.c:51)
==8394== mutex 0xffefff5a0 was first observed at:
==8394==    at 0x4C36719: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==8394==    by 0x4008D3: nearly_main (01_bad_unlock_fixed.c:31)
==8394==    by 0x400948: main (01_bad_unlock_fixed.c:50)
==8394==
==8394==
==8394== For counts of detected and suppressed errors, rerun with: -v
==8394== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 14 from 6)
```

Prijavljuje nam da imamo reinicijalizovane mutekse. Prema dokumentaciji
reinicijalizovanje inicijalizovanog muteksa ima nedefinisano ponašanje i
stoga nam se prijavljuje greška. Muteksi iako su deklarisani u telu
funkcije, ne ponašaju se kao obične lokalne promenljive. Dodajemo na
kraj funkcije `nearly_main` sledeće naredbe:
```c
pthread_mutex_destroy(&mx1);
pthread_mutex_destroy(&mx2);
```

Pokretanje program kroz *Valgrind* sa alatom *drd* ovaj put prolazi bez
greške.
