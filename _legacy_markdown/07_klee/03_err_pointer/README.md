## Primer greške u radu sa pokazivačima

U slučaju da postoji putanja programa na kojoj može doći do nepravilnog
pristupa memorijskim lokacijama, što je čest slučaj pri radu sa
pokazivačima, `Klee` će sam prijaviti grešku i generisati ulaz na osnovu
koga možemo popraviti svoj program. Primer ovakvog programa se može videti u primeru `03_err_pointer`.

Označićemo simbolički ulaz i uključiti potrebno zaglavlje i zatim
sačuvati kod u datoteku `pointer_error_sym.c`. Na osnovu nje ćemo
napraviti odgovarajući bitkod i pokrenuti alat KLEE. KLEE je
pronašao `8` putanja i generisao `5` test primera, a pritom je i javio
`memory error: out of bound pointer`. Test primer koji dovodi do
prijavljene greške će biti označen posebnom datotekom sa ekstenzijom
`.ptr.err`. Primetimo da je broj test primera manji od broja istraženih
putanja.

**BITNO:** `Klee` neće generisati sve moguće ulaze koji dovode do iste
greške. Ukoliko je tako nešto potrebno, prilikom pokretanja dodati
opciju `-emit-all-errors`:
```sh
$ klee –emit-all-errors pointer_error_sym.bc
```

Ako uvedemo pomenutu opciju prilikom pokretanja alata KLEE, biće generisano `8` test primera, od čega `4` označena greškom za memoriju. Čitanjem dobijenih test primera, možemo ispraviti sve putanje koje su dovele do problema sa pokazivačima.

Pokrenuti `klee-stats` nad direktorijumom koji je generisan u prvom
slučaju i sa dodavanjem opcije za emitovanje svih grešaka. Primetiti da
se jedino razlikuje vreme potrošeno na solver dok je pokrivenost koda i
grana identična.
