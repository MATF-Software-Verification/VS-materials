# Statički analizatori (Clang statički analizator i prateći alati)

[Clang](https://clang.llvm.org/) je kompilator otvorenog koda za C familiju jezika. Koristi [LLVM](https://llvm.org/) optimizator i generator koda. Više informacija zajedno sa uputstvima je moguće pronaći u [priručniku](https://clang.llvm.org/docs/UsersManual.html) za Clang kompilator. [Clang statički analizator](https://clang-analyzer.llvm.org/) je deo Clang projekta.

Clang statički analizator koristi razne implementacije [proveravača](https://clang-analyzer.llvm.org/available_checks.html) (engl. _checkers_) prilikom analize. Proveravači su kategorisani u familije - _podrazumevani_ i _eksperimentalni (alpha)_. Podrazumevani proveravači izvršavanju bezbednosne provere, prate korišenje API funkcija, traže mrtav kod i ostale logičke greške. [Eksperimentalni (alpha) proveravači](https://clang-analyzer.llvm.org/alpha_checks.html) nisu podrazumevano uključeni pošto često daju lažne pozitivne rezultate. Uputstvo za implementaciju proveravača se može naći na sledećem [linku](https://clang-analyzer.llvm.org/checker_dev_manual.html).

Neke kategorije podrazumevanih proveravača:
- [Core Checkers](https://clang-analyzer.llvm.org/available_checks.html#core_checkers) vrše provere opšte namene kao što su deljenje nulom, dereferenciranje NULL pokazivača, korišćenje neinicijalizovanih vrednosti itd.
- [C++ Checkers](https://clang-analyzer.llvm.org/available_checks.html#cplusplus_checkers) vrše provere specifične za C++ programski jezik
- [Dead Code Checkers](https://clang-analyzer.llvm.org/available_checks.html#deadcode_checkers) traže mrtav kod
- [Nullability Checkers](https://clang-analyzer.llvm.org/available_checks.html#nullability_checkers) proveravaju dodele ili prosleđivanje NULL pokazivača u kontekstu gde se ne očekuje NULL pokazivač 
- [Optin Checkers](https://clang-analyzer.llvm.org/available_checks.html#optin_checkers) prate neinicijalizovane objekte i virtualne pozive (C++)
- [OS X Checkers](https://clang-analyzer.llvm.org/available_checks.html#osx_checkers) vrše provere specifične za Objective-C i proveravaju upotrebu Apple SDK-a (OS X i iOS)
- [Security Checkers](https://clang-analyzer.llvm.org/available_checks.html#security_checkers) proveravaju nebezbedno korišćenje API-ja i vrše provere na osnovu CERT standarda bezbednog kodiranja
- [Unix Checkers](https://clang-analyzer.llvm.org/available_checks.html#unix_checkers) proveravaju upotrebu Unix i POSIX programerskih interfejsa

Spisak proveravača možemo dobiti opcijom `-Xanalyzer -analyzer-list-enabled-checkers`. Proveravače možemo uključiti zadavanjem opcija Clang analizatoru (analizator pozivamo zadavanjem opcije `--analyze`):
```sh
$ clang \
    -Xanalyzer -analyzer-checker=alpha \
    --analyze divzero.c
```

Alternativno, analizator možemo pokrenuti na jednostavniji način korišćenjem alata koji dolaze uz Clang. Ti alati su posebno korisni u situacijama kada koristimo sisteme za izgradnju projekata.

[scan-build](https://clang-analyzer.llvm.org/scan-build.html) je alat koji dozvoljava korisnicima da pokrenu statički analizator nad izvornim kodom projekta kao deo regularnog procesa izgradnje projekta preko komandne linije. Prilikom izgradnje projekta, kako se izvorni fajlovi prevode, takođe se i analiziraju od strane statičkog analizatora. Nakon završetka procesa izgradnje projekta, rezultati analize se mogu videti kao HTML stranice.

`scan-build` radi tako što menja odgovarajuće promenljive okruženja (engl. _environment variables_), npr. `CC` i `CXX`, sa ciljem da se pokrene "lažni" prevodilac koji prvo pokreće `gcc` ili `clang`, a zatim pokreće i statičku analizu. Ovaj proces stoga radi nezavisno od korišćenog sistema za izgradnju projekta (make, CMake, itd.), sve dok se koriste odgovarajuće promenljive okruženja.

```sh
$ scan-build
USAGE: scan-build [options] <build command> [build options]
```

Primeri pokretanja `scan-build` alata:
```sh
$ scan-build make
$ scan-build make -j4
$ scan-build xcodebuild
```

Moguće je analizirati individualne fajlove:
```sh
$ scan-build gcc -c 1.c 2.c
$ scan-build -internal-stats -stats \
    -o tmp \
    -enable-checker security,deadcode,core,alpha \
    clang -cc1 \
    -analyze -analyzer-display-progress \
    -Werror \
    divzero.c
```

Česte opcije koje se prosleđuju `scan-build` alatu:

| Option | Description |
|---|---|
| `-o` | Target directory for HTML report files. Subdirectories |
|      | will be created as needed to represent separate "runs" | 
|      | of the analyzer. If this option is not specified, a |
|      | directory is created in `/tmp` to store the reports. |
| `-h` (or no arguments) | Display all scan-build options. |
| `-k` `--keep-going` | Add a "keep on going" option to the specified build |
|      | command. This option currently supports `make` and 
|      | `xcodebuild`. This is a convenience option; one can 
|      | specify this behavior directly using build options. |
| `-v` | Verbose output from scan-build and the analyzer. A second |
| | and third `-v` increase verbosity.
| `-V` | Open results in a web browser after the build is completed. |
| `--use-analyzer Xcode` | scan-build uses the 'clang' executable relative to itself for 
|      | static analysis. One can override this behavior with this 
| (`--use-analyzer [clang path]`) | option by using the `clang` packaged with Xcode |
|   |  (on OS X) or from the PATH. |


Izlaz `scan-build` alata je skup HTML fajlova od kojih svaki predstavlja zaseban izveštaj. Zbirni fajl `index.html` se kreira za lak pristup svim izveštajima. Opcija `-o` se može iskoristiti za promenu putanje gde će se sačuvati izveštaji. Ako opcija `-o` nije navedena, `scan-build` će izveštaje sačuvati u `/tmp` direktorijumu. Putanja do izveštaja će biti ispisana od strane `scan-build` alata. Moguće je automatski otvoriti izveštaje nakon završetka analize zadavanjem opcije `-V`. Alternativno, može se koristiti alat `scan-view` za prikazivanje izveštaja `scan-build` alata.

Preporuke za korišćenje `scan-build` alata:
- Projekat **uvek** treba analizirati u _Debug_ konfiguraciji. Pretpostavke i asertacije će biti od koristi analizatoru da smanji prostor pretrage i da značajno smanji broj lažno-pozitivnih upozorenja.
- Koristiti _verbose_ konfiguraciju prilikom debagovanje `scan-build` alata. Opcija `-v` tera `scan-build` da ispisuje dodatne informacije.
- Ako projekat koristi `configure` skriptu generisanu od strane `autoconf` alata, pokrenuti uvek prvo `scan-build` za `configure` skript [^1], pa tek onda za regularnu komandu izgradnje projekta. 

[^1]: `configure` skripte obično generišu `make` fajlove u kojima su hardkodirane putanje do kompilatora, odnosno nisu navedene preko promenljivih okruženja, što znači da scan-build u tim situacijama ne može da ubaci "lažni" prevodilac u proces izgradnje projekta.

Ako želimo deo koda da isključimo iz analize, to možemo uraditi ograđivanjem koda na sledeći način:
```c
#ifndef __clang_analyzer__
// Kod koji ne treba da se analizira
#endif
```


## Primeri

U direktorijumu `09_clang/examples_individual` se mogu pronaći individualni izvorni kodovi koji se mogu analizirati. Primeri se mogu pokrenuti uz pomoć bash skripte `analyze`, dostupne u pomenutom direktorijumu:
```sh
$ ./analyze 01_struct_access.c core,security,alpha -v
```

Primer kompleksnijeg projekta koji koristi `make` sistem za izgradnju se može pronaći u direktorijumu `examples_make`.

