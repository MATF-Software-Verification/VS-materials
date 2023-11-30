#### Primer: Petlje

Matrica se popunjava u `main` funkciji, a čita u funkciji `array_sum`.
Iz konzole izvršavamo komandu:
```sh
$ valgrind --tool=cachegrind --cache-sim=yes ./loops-fast
$ kcachegrind cachegrind.out.*
```

Na ekranu vidimo izveštaj na nivou celog programa i vidimo da program ima preko 125 000 promašaja prilikom čitanja podataka sa D1 i LL nivoa keša.

![cachegrind_1](06_profiling/03_valgrind_cachegrind/01_loops/images/cache1_1.png)

Istaknute su nam konkretne linije u kojima je bilo promašaja, zajedno sa brojem promašaja. Uočavamo da imamo
po 125 000 promašaja obe petlje, i u main i u array sum funkciji.

![cachegrind_2](06_profiling/03_valgrind_cachegrind/01_loops/images/cache1_2.png)

Cela matrica ima `1000 x 1000 x 8B = 8MB`. Veličina keša [^1], npr:
```txt
L1d cache:               32K      
L1i cache:               32K
L2 cache:               256K
L3 cache:              6144K   ---> LL
```

[^1]: Veličina keša i linije na konkretnom procesoru se može saznati izvršavanjem: 
```sh
$ getconf -a | grep CACHE
```

Svakako premali za celu matricu, pa se zbog toga i dogadaju promašaji. Ukoliko bi LL keš bio dovoljno veliki (>8MB)
u funkciji array sum ne bismo imali promašaje na LL nivou, jer se cela matrica učita u keš pre poziva funkcije u petlji
u main funkciji.

Ponovo pokrećemo program, ali ovaj put Cachegrind -u zadajemo 16MB za veličinu LL keša:
```sh
$ valgrind --tool=cachegrind --cache-sim=yes --LL=16777216,8,64 ./loops-fast
```

Izveštaj možemo iz konzole čitati komandom
```sh
$ cg_annotate --auto=yes cachegrind.out.*
```

```txt
--------------------------------------------------------------------------------
I1 cache:         32768 B, 64 B, 8-way associative
D1 cache:         32768 B, 64 B, 8-way associative
LL cache:         16777216 B, 64 B, 2-way associative
Command:          ./loops-fast
Data file:        cachegrind.out.26469
Events recorded:  Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
Events shown:     Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
Event sort order: Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
Thresholds:       0.1 100 100 100 100 100 100 100 100
Include dirs:    
User annotated:  
Auto-annotation:  on

--------------------------------------------------------------------------------
       Ir  I1mr  ILmr        Dr    D1mr  DLmr        Dw    D1mw    DLmw
--------------------------------------------------------------------------------
9,170,730 1,068 1,053 2,040,968 127,541 1,976 1,012,294 125,603 125,487  PROGRAM TOTALS

--------------------------------------------------------------------------------
       Ir I1mr ILmr        Dr    D1mr DLmr        Dw    D1mw    DLmw  file:function
--------------------------------------------------------------------------------
5,004,015    2    2 1,000,004       3    1 1,000,002 125,002 124,928  loops-fast.c:main
4,004,004    1    1 1,000,001 125,001    0         0       0       0  loops-fast.c:array_sum
   56,470    9    9    13,757   1,047  868        17       2       1  /build/glibc-Cl5G7W/glibc-2.23/elf/dl-addr.c:_dl_addr
   21,444   20   20     7,663     187  133     3,329      11       6  /build/glibc-Cl5G7W/glibc-2.23/elf/dl-lookup.c:do_lookup_x
   17,173   10   10     3,626      92   80     1,993      12       8  /build/glibc-Cl5G7W/glibc-2.23/elf/dl-lookup.c:_dl_lookup_symbol_x
   16,311   20   20     3,949     555  535     2,048     243     235  /build/glibc-Cl5G7W/glibc-2.23/elf/../sysdeps/x86_64/dl-machine.h:_dl_relocate_object

--------------------------------------------------------------------------------
-- Auto-annotated source: loops-fast.c
--------------------------------------------------------------------------------
       Ir I1mr ILmr        Dr    D1mr DLmr        Dw    D1mw    DLmw

-- line 3 ----------------------------------------
        .    .    .         .       .    .         .       .       .  #define N 1000
        .    .    .         .       .    .         .       .       .  
        .    .    .         .       .    .         .       .       .  double array_sum(double[N][N]);
        .    .    .         .       .    .         .       .       .  
        .    .    .         .       .    .         .       .       .  double array_sum(double a[N][N])
        .    .    .         .       .    .         .       .       .  {
        .    .    .         .       .    .         .       .       .    int i,j;
        .    .    .         .       .    .         .       .       .    double s;
    2,003    1    1         0       0    0         0       0       0    s=0;
    2,000    0    0         0       0    0         0       0       0    for(i=0;i<N;i++)
2,000,000    0    0         0       0    0         0       0       0      for(j=0;j<N;j++)
2,000,000    0    0 1,000,000 125,000    0         0       0       0        s += a[i][j];
        .    .    .         .       .    .         .       .       .    
        .    .    .         .       .    .         .       .       .    return s;
        1    0    0         1       1    0         0       0       0  }
        .    .    .         .       .    .         .       .       .  
        .    .    .         .       .    .         .       .       .  int main(int argc, char** argv)
    2,007    1    1         1       0    0         1       0       0  {
        .    .    .         .       .    .         .       .       .    double a[N][N];
        .    .    .         .       .    .         .       .       .    int i,j;
        .    .    .         .       .    .         .       .       .    
    2,000    0    0         0       0    0         0       0       0    for(i=0;i<N;i++)
        .    .    .         .       .    .         .       .       .    {
2,000,000    0    0         0       0    0         0       0       0      for(j=0;j<N;j++)
        .    .    .         .       .    .         .       .       .      {
3,000,000    1    1 1,000,000       1    1 1,000,000 125,001 124,928        a[i][j]=0.01;
        .    .    .         .       .    .         .       .       .      }
        .    .    .         .       .    .         .       .       .    }
        .    .    .         .       .    .         .       .       .    
        .    .    .         .       .    .         .       .       .    /* this is just to prevent the compiler
        .    .    .         .       .    .         .       .       .       from optimizing the upper loop away */
        2    0    0         0       0    0         1       1       0    printf("sum = %10.3f\n",array_sum(a));
        .    .    .         .       .    .         .       .       .    
        .    .    .         .       .    .         .       .       .    return 0;
        6    0    0         3       2    0         0       0       0  }

--------------------------------------------------------------------------------
The following files chosen for auto-annotation could not be found:
--------------------------------------------------------------------------------
  /build/glibc-Cl5G7W/glibc-2.23/elf/dl-lookup.c
  /build/glibc-Cl5G7W/glibc-2.23/elf/../sysdeps/x86_64/dl-machine.h
  /build/glibc-Cl5G7W/glibc-2.23/elf/dl-addr.c

--------------------------------------------------------------------------------
Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
--------------------------------------------------------------------------------
98    0    0 98   98    0 99  100  100  percentage of events annotated
```

ili otvaranjem u KCachegrind -u.

![cachegrind_3](06_profiling/03_valgrind_cachegrind/01_loops/images/cache1_3.png)


U programu `loops_slow` se elementima matrice ne pristupa po vrstama već po kolonama.
```sh
$ valgrind --tool=cachegrind --cache-sim=yes ./loops-slow
```

Prilikom učitavanja podataka u keš, učitavaju se zajedno podaci koji su blizu u memoriji pod pretpostavkom da će biti uskoro upotrebljeni. Tako se učitava pored jednog elementa vrste i oni koji su za njim u vrsti jer nam je matrica tako alocirana. U petlji u main funkciji pristupamo jednom elementu, a potom narednom elementu iz iste kolone. Ta dva elementa, za dovoljno veliku matricu ne moraju biti zajedno učitani u keš. Ukoliko je D1 keš veličine 32KB i ako je veličina linije keša 64B, tj. 8 double vrednosti, imamo 512 linija keša. Prilikom pristupanja elementu `a[0][0]`, potrebno ga je dovući u keš D1. Sa njim će u D1 biti učitano i narednih 7, do `a[0][7]`. U narednom koraku nam treba element `a[1][0]` i njega nema u kešu, imamo još jedan promašaj. Možemo imati najviše 512 linija istovremeno prisutnih u kešu stoga posle prvog elementa 512. vrste, moraće da se izbacuju najranije učitane linije, da bi se napravio prostor za nove podatke [^2]. Iz tog razloga imamo 1000000 promašaja na D1 prilikom pisanja u matricu. Nijedan element matrice nije u D1 kešu u trenutku kada je potreban.

[^2]: Pretpostavljamo da je politika zamene linija keša takva da se najranije ubačene linije izbace prve.

![cachegrind_3](06_profiling/03_valgrind_cachegrind/01_loops/images/cache2_1.png)

Ukoliko povećamo D1 keš na 64KB, imaćemo sličnu situaciju kao sa prethodnim programom sa ∼125000 promašaja prilikom pisanja na kešu D1.

```sh
$ valgrind --tool=cachegrind --cache-sim=yes --D1=65536,8,64 ./loops-slow
```

Sa toliko velikim D1 kešom možemo imati 1024 linije u jednom trenutku, pa je onda nakon prvih 1000 promašaja za prvi element svake vrste, istovremeno u D1 keš učitano prvih 8 kolona matrice, pa za narednih 7 kolona nećemo imati promašaje. Dakle, otprilike svaka 8 kolona će generisati novih 1000 promašaja. Iz tog razloga imamo oko 125000
promašaja prilikom pisanja na D1. Programu `loops_fast` je dovoljan duplo manji D1 keš za iste performanse.

