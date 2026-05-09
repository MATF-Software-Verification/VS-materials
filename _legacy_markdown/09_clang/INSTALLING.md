## Provera modela

### Clang

[Clang](https://clang.llvm.org/docs/UsersManual.html) se na većini Linux distribucija može instalirati kroz paket `clang`. Npr., za Ubuntu:
```sh
$ sudo apt-get install clang
```

[scan-build](https://clang-analyzer.llvm.org/scan-build.html) alat za statičku analizu i druge Clang alate koje koristimo kroz interfejs komandne linije na većini Linux distribucija dolaze zajedno sa Clang-om. Za starije verzije je moguće da je neophnodno instalirati paket `clang-tools`.

**Napomena za alat scan-build iz clang-tools skupa alata**: Korisnici Windows operativnog sistema treba da instaliraju Perl kako bi scan-build alat funkcionisao. Na Windows sistemima scan-build se isporučuje kao Batch  skript `scan-build.bat`. Više informacija o specifičnostima za Windows OS u kontekstu korišćenja scan-build alata je moguće naći u [scan-build priručniku](https://clang-analyzer.llvm.org/scan-build.html).
