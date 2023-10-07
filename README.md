---
title: "Verifikacija softvera - Vežbe"
author: [Ivan Ristović]
date: "2023"
keywords: [Software Verification]
abstract: |

    Kolekcija materijala sa vežbi za kurs [Verifikacija softvera](http://www.verifikacijasoftvera.matf.bg.ac.rs/) na Matematičkom fakultetu, Univerziteta u Beogradu.

    Teme i alati rađeni na vežbama:
    - Dijagnoziranje problema
        - Alati za analizu performansi Linux sistema
        - Analiza ponašanja programa metodom crne kutije
    - Debagovanje koristeći alate za debagovanje i razvojna okruženja
        - Debagovanje na niskom nivou ([`gdb`](https://www.sourceware.org/gdb/))
        - Debagovanje C/C++ kodova ([`QtCreator`](https://doc.qt.io/qtcreator/creator-debugging.html))
        - Debagovanje aplikacija nad JVM (Java) ili CLR (C#) ([`IntelliJ IDEA`](https://www.jetbrains.com/idea/), [`Rider`](https://www.jetbrains.com/rider/))
    - Testiranje jedinica koda
        - Pisanje testabilnog koda
        - [`QtTest`](https://doc.qt.io/qt-6/qttest-index.html)
        <!--- , [`Catch`](https://github.com/catchorg/Catch2) (C, C++) --->
        - [`JUnit`](https://junit.org) (Java)
        - [`xUnit`](https://xunit.net/), [`NUnit`](https://nunit.org/) (C#)
    - Praćenje pokrivenosti koda testovima
        - [`lcov`](https://github.com/linux-test-project/lcov) (C, C++)
        - [`JaCoCo`](https://www.jacoco.org/jacoco/) (Java)
        <!--- - [`dotnet-coverage`](https://learn.microsoft.com/en-us/dotnet/core/additional-tools/dotnet-coverage) (C#) --->
    - Testiranje pomoću objekata imitatora
        - Ručno pisanje imitator klasa (C++)
        - Imitatori baza podataka (C#)
        - Biblioteke za testiranje koristeći objekte imitatore - [`Mockito`](https://site.mockito.org/) (Java), [`Moq`](https://github.com/moq) (C#)
    - Fuzz testiranje
        - [`LLVM libFuzzer`](https://llvm.org/docs/LibFuzzer.html)
    - Profajliranje
        - [`Valgrind`](https://valgrind.org/) (memcheck, cachegrind, callgrind, hellgrind, drd)
        - [`perf`](https://perf.wiki.kernel.org/)
        - [`Intel VTune`](https://www.intel.com/content/www/us/en/develop/documentation/vtune-help/top.html)
        - [`eBPF`](https://ebpf.io/)
    - Statička analiza
        - [`KLEE`](https://klee.github.io/)
        - [`CBMC`](https://www.cprover.org/cbmc/)
        - [`Clang`](https://clang.llvm.org/)
    - Alati i jezici za formalnu verifikaciju softvera
        - [`Dafny`](https://dafny.org/)

...


