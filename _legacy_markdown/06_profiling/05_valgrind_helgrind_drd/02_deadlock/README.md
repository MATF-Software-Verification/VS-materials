#### Potencijalno blokiranje niti

*Helgrind* prati redosled kojim niti zaključava promenljive. Na ovaj
način *Helgrind* detektuje potencijalne delove kôda koji mogu dovesti do
blokiranja niti. Na ovaj način je moguće detektovati greške koje se nisu
javile tokom samog procesa testiranja programa, već se javljaju kasnije
tokom njegovog korišćenja.

Ilustracija ovakvog problema:

-   Pretpostavimo da je potrebno zaključati dve promenljive `M1` i `M2`
    da bi se pristupilo deljenom objekatu `O`

-   Zatim da dve niti `T1` i `T2` žele da pristupe deljenoj promenljivoj
    `O`. Do blokoranja niti dolazi kada nit `T1` zaključa `M1` , a u
    istom trenutku `T2` zaključa `M2`. Nakon toga nit `T1` ostane
    blokirana jer čeka da se otključa `M2` , a nit `T2` ostane blokirana
    jer čeka da se otključa `T1`.

*Helgrind* kreira graf koji predstavlja sve promenljive koje se mogu
zaključati, a koje je otkrio u prošlosti. Kada nit naiđe na novu
promenljivu koju zaključava, graf se osveži i proverava se da li graf
sadrži krug u kome se nalaze zaključane promenljive. Postojanje kruga u
kome se nalaze zaključane promenljive je znak da je moguće da će se niti
nekada u toku izvršavanja blokirati. Ako postoje više od dve zaključane
promenljive u krugu problem je još ozbiljniji. Alat *DRD* ne otkriva
ovaj tip grešaka.

Primer `02_dining_philosophers_deadlock` ilustruje deadlock scenario:
```txt
==15457== Thread #6: lock order "0x6010E0 before 0x6012C0" violated
==15457==
==15457== Observed (incorrect) order is: acquisition of lock at 0x6012C0
==15457==    at 0x4C321BC: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==15457==    by 0x40090D: dine(void*) (02_dinning_philosophers_deadlock.cpp:26)
==15457==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==15457==    by 0x4E476B9: start_thread (pthread_create.c:333)
==15457==
==15457==  followed by a later acquisition of lock at 0x6010E0
==15457==    at 0x4C321BC: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==15457==    by 0x400937: dine(void*) (02_dinning_philosophers_deadlock.cpp:27)
==15457==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==15457==    by 0x4E476B9: start_thread (pthread_create.c:333)
==15457==
==15457==  Lock at 0x6010E0 was first observed
==15457==    at 0x4C360BA: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==15457==    by 0x400A0E: main (02_dinning_philosophers_deadlock.cpp:48)
==15457==  Address 0x6010e0 is 0 bytes inside data symbol "_ZL4chop"
==15457==
==15457==  Lock at 0x6012C0 was first observed
==15457==    at 0x4C360BA: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==15457==    by 0x400A0E: main (02_dinning_philosophers_deadlock.cpp:48)
==15457==  Address 0x6012c0 is 480 bytes inside data symbol "_ZL4chop"
```

Ne treba ignorisati činjenicu da nam *Helgrind* prijavljuje narušavanje
relacije, čak iako vidimo da se program lepo završava. Ako svaki filozof
samo jednom ruča, može se dogoditi da nemamo zaključavanje, ali ako
povećamo broj iteracija petlje na 1000 i da svaki filozof želi 1000 puta
ručati, stvari se komplikuju.

Problem se rešava uvođenjem uređenja nad izborom viljuške, jer se tada
nameće i relacija *„desilo se pre"*. Staviti raspored da filozof uvek
bira prvo manju viljušku, pa zatim veću po rednom broju. Kako se sada
ponaša program?

Program `03_deadlock.c` ostaje zaglavljen u mrtvoj petlji i program se ne završava. Otvorimo kôd i primetimo da se u funkcijama `run1` i `run2` uspavljuje program na 10ms između dva zaključavanja muteksa, `mx1` i `mx2` i pre otključavanja. Stavimo te redove pod komentare, privremeno. Nakon toga, pokretanje programa se uspešno završava. Sada, pokrenimo program kroz *Valgrind* sa alatom *Helgrind*. Prijaviće nam poruku, sa narušenim redosledom zaključavanja muteksa, i kao tako, prijavljuje nam mogućnost da imamo mrtvu petlju.

