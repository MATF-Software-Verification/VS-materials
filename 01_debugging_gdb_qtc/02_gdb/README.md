## gdb

_GNU Debugger_ (gdb) je debugger koji se može koristiti za debagovanje (najčešće) C/C++ programa. Preko gdb je moguće pokrenuti program sa proizvoljnim argumentima komandne linije, posmatrati stanje promenljivih ili registara procesora, pratiti izvršavanje kroz naredbe originalnog ili asembliranog koda, postavljanje bezuslovnih ili uslovnih tačaka prekida i sl. Više o gdb se može pročitati [na ovom linku](https://www.sourceware.org/gdb/).

Koristeći gdb možemo učitati program iz prethodnog primera. 
U slučaju da želimo da ručno prevedemo program, neophodno je da se postaramo da je prosleđen `-g` flag `gcc` kompilatoru:
```sh
$ gcc main.c -g -o BufferOverflow
```

Pošto je QtCreator već preveo ovaj program i u `build-*` direktorijum ostavio izvršivi fajl, možemo ga direktno učitati u gdb:
```sh
$ gdb BufferOverflow
...
Reading symbols from BufferOverflow...
(gdb) 
```
Alternativno, možemo program učitati u već pokrenuti gdb proces:
```sh
$ gdb
...
(gdb) file BufferOverflow
Reading symbols from BufferOverflow...
(gdb)
```

U slučaju da debug simboli nisu prisutni, možemo u definiciji projekta dodati odgovarajući flag (pod `QMAKE_CFLAGS`).

Spisak komandi koje gdb pruža možemo dobiti komandom `help`. Za sve ove naredbe postoje i skraćene varijante - npr. za `running` možemo kucati `run` ili samo `r`.

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

Tačke prekida možemo postaviti komandom `breakpoints`, aktiviramo/deaktiviramo komandama `enable`/`disable`, a brišemo komandom `delete`. Komandom `continue` nastavljamo rad programa do naredne tačke prekida. Tačke prekida mogu biti linije, npr. `main.c:15` ali i funkcije, npr. `main` ili `main.c:grant_privilege`. Postavimo tačku prekida na funkciju `grant_privilege`, kontrolišimo izvršavanje programa naredbama `step` (nalik na _step into_) i `next` (nalik na _step over_):
```txt
(gdb) b main.c:grant_privilege
Breakpoint 1 at 0x1171: file ../01_buffer_overflow/main.c, line 5.
(gdb) r
Starting program: BufferOverflow
Breakpoint 1, grant_privilege () at ../01_buffer_overflow/main.c:5
5       {
(gdb) s
7               char ok[16] = "no";
(gdb) n
9               printf("\n Enter the password : \n");
(gdb) n

 Enter the password :
10              scanf("%s", password);
(gdb) n
MyPassword12        if (strcmp(password, "MyPassword")) {
(gdb) info locals
password = "MyPassword\000\367\377\177\000"
ok = "no", '\000' <repeats 13 times>
(gdb) n
15                      printf("\n Correct Password \n");
(gdb) n

 Correct Password
16                      strcpy(ok, "yes");
(gdb) n
19              if (strcmp(ok, "yes") == 0) {
(gdb) n
23                  printf("\n Root privileges given to the user \n\n");
(gdb) n

 Root privileges given to the user

25      }
(gdb) finish
Run till exit from 
#0  grant_privilege () at ../01_buffer_overflow/main.c:25
main () at ../01_buffer_overflow/main.c:43
43              return 0;
```

Komandom `info` možemo dobiti informacije o lokalnim promenljivim, registrima itd. (npr. `info locals` tj. `info registers`).

Alternativno, moguće je iskoristiti drugačiji korisnički interfejs, komandom `tui` npr. `tui enable`. Tako dobijamo pogled na izvorni kod na jednoj polovini korisničkog interfejsa. Komandom `tui reg` možemo dobiti i prikaz registara, npr. `tui reg all`.

Koristeći gdb možemo dodati i uslovne tačke prekida, npr. `b grant_privilege:12 if ok != "no"`. Komandom `info breakpoints` možemo videti spisak tačaka prekida.
