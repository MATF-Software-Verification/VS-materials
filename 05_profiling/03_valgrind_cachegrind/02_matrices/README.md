#### Primer: Množenje matrica

Programi: `matrix_slowest`, `matrix_slower`, `matrix_medium` i `matrix_mediumish`, implementiraju množenje matrica.

`matrix_slowest` program rešava problem naivno primenjujući formulu. Uzrok sporosti izvršavanja tog programa leži u velikom broju promašaja u kešu. Oni nastaju kao posledica toga što je potrebno `i`-tu vrstu matrice `A` pomnožiti skalarno sa `j`-tom kolonom matrice `B`, a elementi kolone se ne nalaze na sukcesivnim adresama u memoriji.

Podesimo `N` na `10` i profajliramo Cachegrind-om. Primećujemo da imamo malo promašaja, najviše na D1.

```txt
==20967== Cachegrind, a cache and branch-prediction profiler
==20967== Copyright (C) 2002-2015, and GNU GPL’d, by Nicholas Nethercote et al.
==20967== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==20967== Command: ./matrix_slow
==20967==
--20967-- warning: L3 cache found, using its data for the LL simulation.
==20967==
==20967== I refs: 2,186,832
==20967== I1 misses: 1,530
==20967== LLi misses: 1,455
==20967== I1 miss rate: 0.07%
==20967== LLi miss rate: 0.07%
==20967==
==20967== D refs: 732,348 (537,801 rd + 194,547 wr)
==20967== D1 misses: 15,790 ( 13,572 rd + 2,218 wr)
==20967== LLd misses: 9,191 ( 7,761 rd + 1,430 wr)
==20967== D1 miss rate: 2.2% ( 2.5% + 1.1% )
==20967== LLd miss rate: 1.3% ( 1.4% + 0.7% )
==20967==
==20967== LL refs: 17,320 ( 15,102 rd + 2,218 wr)
==20967== LL misses: 10,646 ( 9,216 rd + 1,430 wr)
==20967== LL miss rate: 0.4% ( 0.3% + 0.7% )
```

Probajmo da profajliramo program za daleko veće `N`, tako da matrica ne može stati u na keš. Tri matrice 1000x1000 `float` brojeva su dovoljno velike da ne bi bile zajedno u kešu.

Broj promašaja u `main` funkciji bi mogao da se smanji razdvajanjem obrade svake matrice u zasebnu petlju, a ne da se sve 3 matrice inicijalizuju u jednoj dvostrukoj petlji.

Izvršavati svaki program i meriti vreme:
```sh
$ time ./matrix_slowest
$ time valgrind --tool=cachegrind ./matrix_slowest
```
i primetiti koliko puta Valgrind usporava rad programa.

Probati da se zamene neki redosledi petlji, npr, po `col` i `row`, i ispratiti broj promašaja u kešu.
