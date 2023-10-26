### Buffer Overflow primer (gdb)

Program od korisnika očekuje lozinku i, ukoliko je ona ispravna, daje privilegije korisniku i pristup podacima. Bez gledanja u izvorni kod programa, probajmo da "pogodimo" šifru, ili, još gore, da dobijemo privilegije bez pogađanja šifre.

Prvi pokušaj:
```sh
$ ./sample
Input password:
www
Wrong password.
$ strings sample
...
xxxxxxxxxxxxxxx
SECRET
ThisIsASecretPassword
DEBUG
DEBUG:
...
$  ./sample
Input password:
ThisIsASecretPassword
Correct password.
Password check verification passed!
Sensitive data: xxxxxxxxxxxxxxx
cat: /etc/shadow: Permission denied
```

Naravno, za svrhe ovog primera, lozinka je hardkodirana u samom izvršivom fajlu. Dodatno, ukoliko bismo programu dali privilegije, ispisao bi i sadržaj `/etc/shadow` fajla.

Pošto program ima polje za unos teksta, očekujemo da u programu postoji niz karaktera koji će čuvati uneti tekst. Taj niz ima neku predefinisanu dužinu - šta ako je na ulazu više karaktera nego što može da stane u taj niz? Probajmo da unesemo predugačku lozinku:
```sh
$ ./sample
Input password:
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
[1]    230975 segmentation fault (core dumped)  ./sample
$ ./sample
Input password:
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
Wrong password.
Password check verification passed!
[1]    231459 segmentation fault (core dumped)  ./sample
```

Vidimo da, za veoma dugačke lozinke, program dobija `SIGSEGV`, što verovatno znači da prepisujemo memoriju van granica niza za lozinku. Pošto prepisujemo previše memorije, to se detektuje i program odmah dobija `SIGSEGV`. Međutim, ukoliko lozinka nije predugačka, vidimo da unos prolazi proveru lozinke pre dobijanja `SIGSEGV`! Zašto?

Pogledajmo izvorni kod programa kako bismo razumeli šta se dešava. Vidimo da program prima promenljive okruženja (engl. *environment variables*) `DEBUG` i `SECRET` (na osnovu poziva `getenv` funkcije). `SECRET` promenljiva služi za promenu lozinke, dok `DEBUG` promenljiva služi za uključivanje debug moda:
```sh
$ DEBUG= ./sample
DEBUG: Address of user input array:     0x7ffcab1ed9d0
DEBUG: Address of password check var:   0x7ffcab1ed9ec
DEBUG: Address of stored secret array:  0x55b2db0d5023
DEBUG: Current secret: ThisIsASecretPassword
Input password:
wwww
DEBUG: User entered: wwww
DEBUG: Password check var value: 0
Wrong password.
```
Vidimo da, ukoliko se unese pogrešna lozinka, promenljiva za proveru lozinke koja se koristi u uslovu nije ispravno postavljena:
```sh
$ DEBUG= ./sample
DEBUG: Address of user input array:     0x7ffd1183dda0
DEBUG: Address of password check var:   0x7ffd1183ddbc
DEBUG: Address of stored secret array:  0x564acefaa023
DEBUG: Current secret: ThisIsASecretPassword
Input password:
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
DEBUG: User entered: wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
DEBUG: Password check var value: 2004318071
Wrong password.
Password check verification passed!
Sensitive data:
cat: /etc/shadow: Permission denied
```

Na osnovu ispisanih adresa, vidimo da se ta promenljiva nalazi odmah posle niza za unos. Ukoliko prekoračimo niz, prepisaćemo vrednost te promenljive. Iskoristimo `gdb` da bismo potvrdili da se to zapravo dešava (pritom sada pokrećemo program bez `DEBUG` promenljive):
```sh
$ gdb ./sample
```

Spisak komandi koje gdb pruža možemo dobiti komandom `help`. Za sve ove naredbe postoje i skraćene varijante - npr. za `running` možemo kucati `run` ili samo `r`. Prazna komanda ponavlja prethodno izvršenu komandu.

```sh
(gdb) help
List of classes of commands:

aliases -- User-defined aliases of other commands.
breakpoints -- Making program stop at certain points.
data -- Examining data.
files -- Specifying and examining files.
internals -- Maintenance commands.
obscure -- Obscure features.
running -- Running the program.
stack -- Examining the stack.
status -- Status inquiries.
support -- Support facilities.
text-user-interface -- TUI is the GDB text based interface.
tracepoints -- Tracing of program execution without stopping the program.
user-defined -- User-defined commands.
```

Komandom `info` možemo dobiti informacije o lokalnim promenljivim, registrima itd. (npr. `info locals` tj. `info registers`).
Komandom `info breakpoints` možemo videti spisak tačaka prekida.

Alternativno, moguće je iskoristiti drugačiji korisnički interfejs, komandom `tui` npr. `tui enable`. Tako dobijamo pogled na izvorni kod na jednoj polovini korisničkog interfejsa. Komandom `tui reg` možemo dobiti i prikaz registara sa `tui reg all`.

Tačke prekida možemo postaviti komandom `breakpoints`, aktiviramo/deaktiviramo komandama `enable`/`disable`, a brišemo komandom `delete`. Komandom `continue` nastavljamo rad programa do naredne tačke prekida. Tačke prekida mogu biti linije, npr. `main.c:15` ali i funkcije, npr. `main` ili `main.c:main`. 
Koristeći gdb možemo dodati i uslovne tačke prekida, npr.: 
```txt
(gdb) b main.c:36 if privileged != 0
```

Postavimo tačku prekida na funkciju `main`, i kontrolišimo izvršavanje programa naredbama `step` (nalik na _step into_) i `next` (nalik na _step over_):
```txt
(gdb) b main.c:main
Breakpoint 1 at 0x1192: file main.c, line 14.
(gdb) r
Starting program: ... /sample
Breakpoint 1, main () at main.c:14
14      int main() {
(gdb) s
15          char pwd[PWD_SIZE];
(gdb) s
16          int privileged = 0;
(gdb) s
17          char *sensitive_data = "xxxxxxxxxxxxxxx";
(gdb) s
19          char *secret = getenv("SECRET");
(gdb) n
20          if (secret == NULL) {
(gdb) n
21              secret = "ThisIsASecretPassword";
(gdb) n
24          if (getenv("DEBUG") != NULL) {
(gdb) n
28          dbg("Address of user input array    : %p\n", pwd);
(gdb) n
29          dbg("Address of password check var  : %p\n", &privileged);
(gdb) n
30          dbg("Address of stored secret array : %p\n", secret);
(gdb) n
31          dbg("Current secret: %s\n", secret);
(gdb) n
33          printf("Input password:\n");
(gdb) n
Input password:
34          scanf("%s", pwd);
(gdb) n
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
36          dbg("User entered: %s\n", pwd);
(gdb) info locals
pwd = 'w' <repeats 16 times>
privileged = 2004318071
sensitive_data = 0x555555550077 <error: Cannot access memory at address 0x555555550077>
secret = 0x555555556023 "ThisIsASecretPassword"
(gdb) p pwd
$1 = 'w' <repeats 16 times>
(gdb) p privileged
$2 = 2004318071
(gdb) p &pwd
$1 = (char (*)[16]) 0x7fffffffce80
(gdb) p &privileged
$2 = (int *) 0x7fffffffce9c
(gdb) p pwd[17]
$6 = 119 'w'
(gdb) p/x privileged
$1 = 0x77777777
(gdb) finish
```

Karakter `'w'` ima heksadecimalni kod 77, i vidimo da promenljiva `privileged` takođe ima vrednost `0x77777777` - dakle naš unos je pregazio memoriju promenljive. Jasno je da smo mogli da pažljivo odaberemo unos tako da promenljivu postavimo na koju god vrednost želimo! 

Da bismo sprečili napade prekoračenjem bafera savet je da se primenjuju dobre programerske prakse i da se:
- preoverava upravljanje memorijom tokom programa koristeci neki od alata poput `valgrind memcheck`
- upotrebljava `fgets()` funkcije umesto `gets()` ili `scanf()` koje ne vrše provere granica promenljivih.
- upotrebljava `strncmp()` umesto `strcmp()`, `strncpy()` umesto `strcpy()`, itd.
