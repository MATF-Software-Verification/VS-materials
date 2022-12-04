

# Instalacije
## Alati za debagovanje i razvojna okruženja

### QtCreator

Instalirati QtCreator sa [zvanične stranice](https://www.qt.io/download). Alternativno, moguće je i instalirati ceo Qt radni okvir koji uključuje i QtCreator.

Za neke Linux distribucije je dostupan paket `qt<VERZIJA>-creator`.

### gdb

Za većinu Linux distribucija je dostupan paket `gdb`. `gdb` je za neke distribucije deo paketa za razvoj (npr. `build-essential` za Ubuntu).

## Alati/Biblioteke za testiranje jedinica koda i pokrivenosti koda

### gcov, lcov

`gcov` dolazi podrazumevano uz `gcc` kompajler. Alat `lcov` je obično dostupan u okviru paketa sa istim imenom. Instalacija na Ubuntu distribuciji bi, na primer, izgledala ovako:
```sudo apt-get install lcov```

### Gradle

Da bi se Gradle instalirao, neophodno je na sistemu imati verziju JDK-a veću od 8.  Gradle se potom jednostavno instalira kroz `gradle` za većinu popularnih Linux distribucija. Alternativno, moguće je preuzeti [unapred spremne Gradle artifakte](https://gradle.org/releases) i ručno instalirati Gradle. Primeri pretpostavljaju da je izvršivi fajl (ili alias) `gradle` dostupan na `PATH`-u i pokreće Gradle alat.

Neobavezno za ovaj primer, za laku organizaciju u okruženju sa više različitih JDK verzija, može se koristiti alat [SDKMAN](https://sdkman.io/). Gradle se može instalirati korišćenjem SDKMAN-a: 
```sh
$ sdk install gradle <verzija>
```
Na primer:
```sh
$ sdk install gradle 7.5.1
```
### xUnit / NUnit

`xUnit` i `NUnit` se jednostavno instaliraju sa NuGet repozitorijuma ([xUnit](https://www.nuget.org/packages/xUnit), [NUnit](https://www.nuget.org/packages/xUnit)) ili uz pomoć IDE-a, ili kroz komande:
```sh
$ dotnet add package xunit --version 2.4.2
$ dotnet add package NUnit --version 3.13.3
```
## Alati/Biblioteke za Mock testiranje

### Moq

`Moq` se jednostavno instalira sa [NuGet repozitorijuma](https://www.nuget.org/packages/Moq) ili uz pomoć IDE-a, ili kroz komandu:
```sh
$ dotnet add package Moq --version 4.18.2
```
## Profajleri
### Valgrind

Valgrind se na većini Linux distribucija može instalirati kroz paket `valgrind`. Npr., za Ubuntu:
```sh
$ sudo apt-get install valgrind
```

Za grafički prikaz izveštaja nekih Valgrind-ovih alata može se koristiti program _KCachegrind_. Instalacija, npr., za Ubuntu:
```sh
$ sudo apt-get install kcachegrind
```
### Perf

Perf se na većini Linux distribucija može instalirati kroz paket `perf`. Npr., za Ubuntu:
```sh
$ sudo apt-get install perf
```
## KLEE

KLEE se može instalirati prateći uputstva na zvaničnoj [stranici](https://klee.github.io/getting-started/).
## Provera modela

### CBMC

[CBMC](https://www.cprover.org/cbmc/) se na većini Linux distribucija može instalirati kroz paket `cbmc`. Npr., za Ubuntu:
```sh
$ sudo apt-get install cbmc
```

