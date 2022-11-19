### Massif

Massif je profajer hip memorije - beleži iskorišćen prostor i dodatne bajtove koji se zauzimaju radi poravnanja i vodenja evidencije bajtova u upotrebi. Može da meri i zauzeće memorije na steku, ali to ne radi bez uključivanja dodatne opcije (`--stacks=yes`) jer dosta usporava rad alata. 

Profajliranje hip memorije nam može pomoći da eventalno smanjimo korišćenu memoriju i da otkrijemo neka curenja memorije koja se ne mogu prepoznati Memcheck -om. Prevashodno kad memorija nije još uvek izgubljena, imamo pokazivač, ali nije u upotrebi. Kod takvih programa nepotrebno se povećava memorija koja se koristi tokom vremena. Massif nam može reći i koliko memorije na hipu program koristi i tačnu liniju koda koja je zaslužna za njegovu alokaciju.

Kao i pri upotrebi drugih Valgrind alata, program prevodimo sa informacijama debug sombolima (opcija `-g`). Optimizacija neće uticati na količinu upotrebljene memorije. Massif svoj izveštaj upisuje u datoteku `massif.out.<pid>`, gde je `<pid>` ID procesa. Ukoliko želimo da se upiše u drugu datoteku koristimo opciju `--massif-out-file` i navedemo naziv izlazne datoteke. Informacije iz izveštaja prikazujemo programom `ms_print` prosledujući mu datoteku sa izveštajem.

`ms_print` proizvodi graf koji prikazuje zauzeće memorije tokom izvršavanja programa, kao i detaljnije informacije o različitim tačkama programa koje su odgovorne za alokaciju/dealokaciju memorije. Vrednosti na y osi predstavljaju presek stanja iskorišćenosti memorije u odredenom vremenskom trenutku. Na x osi, Massif podrazumevano koristi broj izvršenih instrukcija kao jedinicu vremena. To se može promeneti opcijom `--time-unit=B` da nam jedinica vremena bude broj bajtova alociran/dealociran na hipu.

Massif pravi preseke stanja iskorišćenosti memorije za svaku alokaciju i dealokaciju hipa, ali ako se program duže izvršava Massif ređe pravi preseke. Kada dostigne maksimalni broj preseka on odbaci oko pola ranijih preseka. Podrazumevan broj preseka koje čuva je 100, ali se to može promeniti opcijom `--max-snapshots`. Detaljnije obradeni preseci su na grafu predstavljeni simbolom `@`. Podrazumevano detaljnije obraduje svaki deseti presek, ali se i to može promeniti opcijom `--detailed-freq`.

```sh
$ valgrind --tool=massif ./massif_example.out
```

Na grafu je simbolom `#` predstavljen još jedan detaljan presek koji je obraden i ujedno je i presek sa najvećim iskorišćenjem memorije. Odredivanje preseka sa najvećim iskorišćenjem memorije nije uvek tačno jer Massif uzima u obzir samo preseke kod kojih se desila dealokacija. Time se izbegava mnogo nepotrebnih pravljenja preseka za najveću iskorišćenost memorije, npr. u slučaju da program iz više navrata alocira dosta memorije, i svaki put to je nova najveća iskorišćenost memorije. Takode, ako program nikada ne dealocira memoriju, nećemo ni imati ovakav presek. Takode ako program i dealocira memoriju ali kasnije alocira još veći blok koji kasnije ne oslobodi, imaćemo presek sa najvećom iskorišćenosti memorije, ali će on biti dosta niži od stvarnog.

Alat Massif meri samo hip memoriju, tj. onu koju smo alocirali funkcijama `malloc`, `calloc`, `realloc`, `memalign`, `new`, `new[]`. Ne meri memoriju alociranu sistemskim pozivima kao što su `mmap`, `mremap`, `brk`. Ukoliko nam je od značaja merenje celokupne alocirane memorije, potrebno je uključiti opciju `--pages-as-heap=yes`. Sa ovom opcijom Massif neće profajlirati hip memoriju, već stranice u memoriji.
