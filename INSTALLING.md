

# Instalacije
## Alati za debagovanje i razvojna okruženja

### gdb

Za većinu Linux distribucija je dostupan paket `gdb`. `gdb` je za neke distribucije deo paketa za razvoj (npr. `build-essential` za Ubuntu).

Popularne modifikacije i front-end prikazi informacija koje gdb pruža:
- [gdb-dashboard](https://github.com/cyrus-and/gdb-dashboard)
- [gdb-frontend](https://debugme.dev/) ([repozitorijum](https://github.com/rohanrhu/gdb-frontend))

### QtCreator

Instalirati QtCreator sa [zvanične stranice](https://www.qt.io/download). Alternativno, moguće je i instalirati ceo Qt radni okvir koji uključuje i QtCreator.

Za neke Linux distribucije je dostupan paket `qt<VERZIJA>-creator`.
### Java agenti

Za pokretanje primera su dovoljni [JDK](https://www.oracle.com/java/technologies/downloads/) i [Maven](https://maven.apache.org/).
Na primer, za Ubuntu OS, dovoljno je preuzeti OpenJDK i Maven:
```sh
$ apt-get install default-jdk    # JDK 8, 11, 17, 21 su LTS
$ apt-get install openjdk-17-jdk # alternativno, specificna verzija
$ java -version                  # proveriti instalaciju
$ apt-get install maven
$ mvn -version
```

Za neke alate i skripte je neophodno postaviti `JAVA_HOME` promenljivu okruženja na direktorijum JDK instalacije:
```sh
$ export JAVA_HOME=/path/to/jdk
$ $JAVA_HOME/bin/java -version
```

Obično se `$JAVA_HOME/bin` postavi na `PATH` kako bi se `java*` alati lakše pokretali:
```sh
$ export PATH=$PATH:$JAVA_HOME/bin
$ which java
/path/to/jdk/bin/java
$ java -version
```
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
## Simboličko izvršavanje

### KLEE

KLEE se može instalirati prateći uputstva na zvaničnoj [stranici](https://klee.github.io/getting-started/). Preporučeno je koristiti Docker kontejner:
```sh
$ docker pull klee/klee:3.0
$ docker run --rm -ti --ulimit='stack=-1:-1' klee/klee:3.0
```
## Provera modela

### CBMC

[CBMC](https://www.cprover.org/cbmc/) se na većini Linux distribucija može instalirati kroz paket `cbmc`. Npr., za Ubuntu:
```sh
$ sudo apt-get install cbmc
```

## Provera modela

### Clang

[Clang](https://clang.llvm.org/docs/UsersManual.html) se na većini Linux distribucija može instalirati kroz paket `clang`. Npr., za Ubuntu:
```sh
$ sudo apt-get install clang
```

[scan-build](https://clang-analyzer.llvm.org/scan-build.html) alat za statičku analizu i druge Clang alate koje koristimo kroz interfejs komandne linije na većini Linux distribucija dolaze zajedno sa Clang-om. Za starije verzije je moguće da je neophnodno instalirati paket `clang-tools`.

**Napomena za alat scan-build iz clang-tools skupa alata**: Korisnici Windows operativnog sistema treba da instaliraju Perl kako bi scan-build alat funkcionisao. Na Windows sistemima scan-build se isporučuje kao Batch  skript `scan-build.bat`. Više informacija o specifičnostima za Windows OS u kontekstu korišćenja scan-build alata je moguće naći u [scan-build priručniku](https://clang-analyzer.llvm.org/scan-build.html).
## Jezici za programiranje i formalnu verifikaciju

### Dafny

Uputstvo za installaciju Dafny jezika se može naći unutar [Dafny repozitorijuma](https://github.com/dafny-lang/dafny/wiki/INSTALL).

