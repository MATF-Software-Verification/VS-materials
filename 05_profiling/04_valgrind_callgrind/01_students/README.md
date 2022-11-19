#### Primer: Studenti

Program učitava imena i prezimena studenata iz datoteke `students.txt` i predmete iz datoteke `subjects.txt` i potom ispisuje informacije o studentima i prosečnim ocenama, po predmetu i u globalu. Ukupno 100 studenata sa po 100 ocena iz svakog od 40 predmeta. Spiskovi sa studentskim rezultatima ispisuju se 10 puta. Analiziramo program Callgrind-om:
```sh
$ valgrind --tool=callgrind --cache-sim=yes ./students.out
```

Otvaramo izveštaj u KCachgrind-u. Gledamo sa leve strane broj pozivanja svake funkcije i broj instrukcija koji je zahtevalo njeno izvršavanje, samostalno i uključujući izvršavanja drugih funkcija koje je pozivala. Sa desne strane moˇzemo izabrati prikaz mape poziva i sa izborom _All Callers_, videćemo koje su sve funkcije pozivale funkciju od interesa.

![callgrind_1](05_profiling/04_valgrind_callgrind/01_students/images/call1_1.png)

Nas zanima zašto se funkcija iz standardne biblioteke toliko puta poziva, 2020 puta. Ako iz alata pogledamo izvorni kod videćemo da se u pri samom početku funkcije `printClass` konstruktor kopije za `std::vector` poziva 10 puta. To je baš broj koliko puta generišemo izveštaj i broj poziva ove funkcije. Problem je što se ceo vektor studenata u funkciju prenosi po vrednosti, a ne po referenci i prilikom svakog poziva vrši se kreiranje kopije za konkretan poziv. Izmenimo kod i primetno ćemo ubrzati izvršavanje programa.
