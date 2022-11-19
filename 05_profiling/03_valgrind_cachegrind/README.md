### Cachegrind

Merenje performansi keša je postalo važno jer se eksponencijalno pove ́ćava razlika u brzini RAM memorije i performansi procesora. Uloga keša je da premosti tu razliku u brzini. Da bismo utvrdili koliko je keš sposoban da to učini prate se pogodci (_hits_) i promašaji (_misses_) keša. Jedan od koraka za poboljšanje je da se smanji broj promašaja na najvišim nivoima keša.

Cachegrind je alat koji omogućava softversko profajliranje keš memorije tako što simulira i prati pristup keš memoriji mašine na kojoj se program, koji se analizira, izvršava. Može se koristiti i za profajliranje izvršavanja grana, korišćenjem opcije `--branch-sim=yes`. Cachegrind simulira memoriju mašine, koja ima prvi nivo keš memorije podeljene u dve odvojene nezavisne sekcije:
**I1** - sekcija keš memorije u koju se smeštaju instrukcije
**D1** - sekcija keš memorije u koju se smeštaju podaci

Drugi nivo keš memorije koju Cachegrind simulira je objedinjen - **LL**, skraćeno od eng. _last level_. Ovaj način konfiguracije odgovara mnogim modernim mašinama. Postoje mašine koje imaju i tri ili četiri nivoa keš memorije. U tom slučaju, Cachegrind simulira pristup prvom i poslednjem nivou. Generalno gledano, Cachegrind simulira I1, D1 i LL (poslednji nivo keš memorije). Cachegrind prikuplja sledeće statističke podatke o programu koji analizira:
- O čitanjima instrukcija iz keš memorije:
    - **Ir** - ukupan broj izvršenih instrukcija
    - **I1mr** - broj promašaja čitanja instrukcija iz keš memorije nivoa I1
    - **ILmr** - broj promašaja čitanja instrukcija iz keš memorije nivoa LL
- O čitanjima brze memorije:
    - **Dr** - ukupan broj čitanja memorije
    - **D1mr** - broj promašaja čitanja nivoa keš memorije D1
    - **DLmr** - broj promašaja čitanja nivoa keš memorije LL
- O pisanjima u brzu memoriju:
    - **Dw** - ukupan broj pisanja u memoriji
    - **D1mw** - broj promašaja pisanja u nivo keš memorije D1
    - **DLmw** - broj promašaja pisanja u nivo keš memorije LL
- O izvršavanju grana:
    - **Bc** - broj uslovno izvršenih grana
    - **Bcm** - broj promašaja uslovno izvršenih grana
    - **Bi** - broj indirektno izvršenih grana
    - **Bim** - broj promašaja indirektno izvršenih grana

Broj pristupa D1 delu keš memorije je jednak zbiru statistika D1mr i D1mw. Ukupan broj pristupa LL nivou jednak je zbiru ILmr, DLmr i DLmw. Primeri u C/C++ koji proizvode indirektno grananje su pozivi funkcija preko pokazivača na funkcije ili pozivi virtuelnih funkcija i `switch` naredbe. Uslovne grananje se generše `if` naredbama i uslovnim ternarnim operatorom
`?:`.

Statistika se prikuplja na nivou celog programa, kao i pojedinačno na nivou funkcija. Na modernim mašinama L1 promašaj košta oko 10 procesorskih ciklusa, LL promašaj košta oko 200 procesorskih ciklusa, a promašaji uslovno i indirektno izvršene grane od 10 do 30 procesorskih ciklusa. Detaljno profajliranje upotrebe keš memorije može pomoći u poboljšanju performansi programa. Izvršavanjem komande `lscpu` na Linux sistemima, dobićemo informacije o veličini keša na mašini na kojoj radimo.

Program koji želimo da analiziramo propuštamo kroz Cachegrind navodeći opciju `--tool=cachegrind`. Za razliku od ostalih Valgrind alata želimo uključenu optimizaciju, tako da ne koristimo opciju `-O0` prilikom prevođenja programa. Kompilacija treba da bude sa optimizacijom, jer nema smisla ovako profajlirati kod koji je drugačiji od onoga koji će se normalno izvršavati. Na standardni izlaz se ispisuju sumarne informacije na nivou celog programa, dok se detaljne informacije upisuju u `cachegrind.out.<pid>` datoteku, gde `<pid>` predstavlja ID procesa. Alat grupiše sve troškove po datotekama i funkcijama kojima ti troškovi pripadaju.

Detaljniji izveštaj možemo videti iz iste datoteke korišćenjem alata `cg_annotate`. Ukoliko imamo izveštaje iz više pokretanja Cachgrind-a za isti program, možemo ih sumirati u jednu datoteku korišćenjem alata `cg_merge` i njegov izlaz kasnije pregledati alatom `cg_annotate`. Moguće je i praviti razliku izmedu više izveštaja Cachgrind-a pomoću alata `cg_diff` i njegov izlaz, slično, otvoriti pomoću `cg_annotate`. Ukoliko modifikujemo kod, to nam može biti od korisiti da pratimo kako modifikacija utiče na performanse programa. Programom `cg_annotate` podrazumevano se prikazuje izveštaj sumiran po funkcijama.

Ako kolona sadrži samo tačkicu, to označava da funkcija ne sadrži instrukcije koje bi prouzrokovale taj dogadaj. Ukoliko u koloni za ime funkcije stoji `???`, to znači da nije bilo moguće odrediti ime na osnovu simbola za debagovanje. Ukoliko većina redova sadrži `???` za ime funkcije program verovatno nije preveden sa debug simbolima (opcija `-g`).

Ukoliko želimo da vidimo izveštaj o broju promašaja po linijama koda, potrebno je da prosledimo izvorne datoteke programu `cg_annotate` ili da uključimo opciju `--auto=yes` kada će se anotirati svaki izvorni kod koji se može naći.

Daleko preglednije je gledati izveštaj pomoću alata KCachgrind.

