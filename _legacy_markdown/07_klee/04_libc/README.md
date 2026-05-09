## Korišćenje C bibliotečkih funkcija i simboličkog okruženja

U slučaju da se koristi KLEE za program koji radi sa C bibliotečkim
funkcijama, potrebno je navesti opcije `–libc=uclibc –posix-runtime`
koje omogućavaju ispravno linkovanje i dodatne opcije za rad sa
simboličkim okruženjem. Sa opcijom `–allow-external-sym-calls` se
omogućava pozivanje spoljnih funkcija sa simboličkim vrednostima u
programu. [@option]

Dodatne opcije za rad sa simboličkim okruženjem:
1.  `–sym-arg <N>` - simbolički argument dužine najviše N  
1.  `–sym-args <MIN> <MAX> <N>` - najmanje MIN, a najviše MAX
    simboličkih argumenata komandne linije, svi maksimalne dužine N  
1.  `–sym-files <NUM> <N>` - NUM simboličkih datoteka veličine N (ne
    uključujući stdin)  
1.  `–sym-files <NUM> <N>` - NUM simboličkih datoteka veličine N (ne
    uključujući stdin)  
1.  `–sym-stdin <N>` - simbolički standardni ulaz veličine N  
1.  `–sym-stdout` - simbolički standardni izlaz

Nevezano za simboličko okruženje, korisno je koristiti i opciju
`–optimize` koja eliminiše mrtav kod prilikom eksploatisanja putanji
čime se dobija na efikasnosti, tj. bržem izvršavanju. Ono što treba
imati u vidu, svaki poziv eksterne funkcije prilično usložnjava
pronalaženje putanja i generisanje test primera.


### Primer sa simboličkim argumentom komandne linije

Primer `04_libc` sadrži program za validaciju lozinke jednog
sistema koja se zadaje kao argument komandne linije i za koju jedino
znamo da je maksimalne dužine `100`. Pretpostaviti da postoji samo jedna
valjana kombinacija za lozinku. Zadatak je pronaći lozinku bez rešavanja
zadatih jednačina koje su postavljenje u programu.

Zadatak ćemo rešiti označavanjem putanje koja nas zanima pozivom
funkcije `klee_assert(0)`, a to je upravo nakon ispisa poruke o uspešno
pronađenoj lozinki (datoteka `password_sym.c`). Nakon što se generiše
bitkod `password_sym.bc`, dodajemo potrebne opcije prilikom poziva
KLEE alata:

```sh
$ klee –optimize –libc=uclibc –posix-runtime password_sym.bc -sym-arg 100
```

Nakon što je prošlo par sekundi, može se primetiti da je generisana samo
jedna poruka o grešci i čak `102` putanje. Da bismo dobili onu koja nas
zanima, izvući ćemo naziv datoteke ekstenzije `.err` i pročitati
odgovarajuću `.ktest` datoteku:
```sh
$ ls klee-last/*err
klee-last/test000026.assert.err
$ ktest-tool test000026.ktest
```
```txt
ktest file : 'test000026.ktest'
args       : ['password_sym.bc', '-sym-arg', '100']
num objects: 2
object    0: name: 'arg0'
object    0: size: 101
object    0: data: 'Pandi_panda\x00\xff\xff\xff\xff
\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff
\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff
\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff
\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff
\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff
\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff
\xff\xff\xff\xff\xff\xff\xff'
object    1: name: 'model_version'
object    1: size: 4
object    1: data: 1
```

Dobili smo da je ulaz `Pandi_panda` koji prati terminirajuća nula
ispravna lozinka.

