# "Fuzz" testiranje

Jedna od tehnika pronalaženja grešaka u programu koja se pokaza vrlo
efikasna je tehnika *fuzz testiranja* (eng. *fuzzing*). Prilikom takvog
testiranja, programu se šalju neočekivani i loši ulazni podaci, u cilju
otkrivanja ulaza koji izaziva greške. Da bi se kreirali fuzz testovi,
standardni fuzzer alati će ili mutirati postojeće testove ili generisati
testove na osnovu definisane gramatike ili skupa pravila. Još efikasniji
način je fuzz testiranje vođeno pokrivenošću kôda (eng. *coverage guided
fuzzing*). Prate se putanje prilikom izvršavanja da bi se generisali još
efikasniji testovi u cilju postizanja maksimalne pokrivenosti kôda, tako
da svaka grana u kôdu bude pokrivena. Tako rade postojeći alati za fuzz
testiranje, kao što su American Fuzzy Lop (AFL), LLVM libFuzzer i
HonggFuzz.

U najjednostavnijim slučajevima potrebno je da izolujemo funkcionalnost
koju bismo da testiramo i ispišemo par pratećih linija kôda i
kompajliramo i pokremo fuzzer. Fuzzer će izvršiti hiljade ili desetine
hiljada testova po sekundi i sačuvaće one intersantne koji povećavaju
pokrivenosti ili izazivaju određeno ponašanje.

Prvi korak u upotrebi *libFuzzer*-a na nekoj biblioteci koju bi trebalo
testirati je kreiranje funkcije koja se u literaturi zove *fuzz target*.
Ta funkcija prihvata niz bajtova i na njih primenjuje neko funkcije iz
biblioteke koju testiramo.

```cpp
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    DoSomethingInterestingWithMyAPI(Data, Size);
    return 0;  // vrednosti osim 0 i -1 su rezervisane
}
```

Ova funkcija ne zavisi ni u kojoj meri od *libFuzzer*-a, pa ju je moguće
i poželjno koristiti i sa drugim alatima za fuzz testiranje npr. AFL i/ili Radamsa.

Važne činjenice o fuzz funkciji (fuzz target):

-   Alat za fuzz testiranje će izvršiti ovu funkciju mnogo puta sa
    različitim ulazima u okviru istog procesa.

-   Mora tolerisati sve vrste ulaznih podataka (prazne, velike, loše
    formatirane, itd.)

-   Ni za jedan ulaz se ne sme pozivati `exit()`.

-   Može koristiti niti, ali idealno bi bilo da sve niti budu spojene na
    kraju funkcije.

-   Mora biti deterministička, koliko god je moguće. Nedeterminizam, kao
    što su nasumične odluke nezavisne od ulaznih bajtova, učiniće fuzz
    testiranje neefikasnim.

-   Mora biti brza. Pokušajte zaobići kubne i veće složenosti, logovanje
    ili preveliko trošenje memorije.

-   Idealno bi bilo da ne modifikuje nijedno globalno stanje (iako to
    nije strogo neophodno).

-   Obično je što uža funkcija to bolja, u smislu, ako funkcija može da
    parsira više formata ulaza, treba je izdeliti na nekoliko fuzz
    funkcija, po jedna po formatu.

*LibFuzzer* koristi sanitajzer za pokrivenost kôda kojim se
instumentalizuje kôd da bi fuzzer mogao da dobija informacije o
pokriventosti koje navode dalje fuzz testiranje. Može se podešavati
opcijom `-fsanitize-coverage` *clang* kompajlera.

Trebalo bi uključiti još neki od sanitajzera, koji mogu pomoći u
otkrivanju grešaka prilikom izvršavanja programa:

- **AddressSanitizer (ASAN)** detektuje grešeke sa memorijom, uključuje se opcijom `-fsanitize=address`.

- **UndefinedBehaviorSanitizer (UBSAN)** detektuje upotrebu različitih mogućnosti C/C++ koje su eksplicitno izdvojene jer uzrokuju nedefinisano ponašanje. Uključiti opcijom `-fsanitize=undefined` `-fno-sanitize-recover=undefined` ili nekom drugom *UBSAN* proverom, npr. `-fsanitize=signed-integer-overflow` `-fno-sanitize-recover=undefined`. Može se kombinovati sa *ASAN* u istom prevođenju.

- **MemorySanitizer (MSAN)** detektuje upotrebu neinicijalizovanih vrednosti, kôd čije ponašanje zavisi od sadržaja neinicijalizovane memorijske lokacije. Uključuje se opcijom `-fsanitize=memory`. *MSAN* se ne sme kombinovati sa drugim sanitajzerima i treba ga koristiti u zasebnom prevođenju.

## Korpus

Fuzzeri, kao *libFuzzer*, koji koriste pokrivenost kôda za generisanje
testova, oslanjaju se na korpus prethodno datih testova za test koji se
testira. Korpus treba da bude idealno odemerena kolekcija validnih i
nevalidnih ulaznih podataka. Fuzzer generiše nasumičnim mutacijama nove
testove od datih iz trenutnog korpusa. Ako mutacija aktivira izvršavanje
prethodno nepokrivene putanje u kôdu koji se testira, tada se mutacija
čuva kao nov test u korpus i služi za buduće varijacije.

*LibFuzzer* može da radi bez inicijalnog test primera, ali će biti manje
efikasan ako bibilioteka koja se testira prihvata kompleksne i
struktuirane ulaze. Korpus može da posluži i za proveru, da li svi
ranije pronađeni testovi i dalje rade bez problema kada se propuste kroz
kôd.

Ako imamo veliki korpus, bilo da je dobijen faz testiranje ili
drugačije, ukoliko želimo da ga smanjimo tako da zadržimo pokrivenost,
to možemo uraditi upotrebom opcije `-merge=1`.
```sh
$ mkdir NEW_CORPUS_DIR  # Store minimized corpus here.
$ ./my_fuzzer -merge=1 NEW_CORPUS_DIR FULL_CORPUS_DIR
```

Ista opcija se može koristiti da se doda još testova u postojeći korpus.
Samo oni testovi koji povećavaju pokrivenost će biti dodati u prvi
navedeni korpus.

```sh
$ ./my_fuzzer -merge=1 CURRENT_CORPUS_DIR NEW_POTENTIALLY_INTERESTING_INPUTS_DIR
```

Da bi se pokrenuo fuzzer sa korpusom testova, prvo treba kreirati
direktorijum sa inicijalnim test primerima i potom ga pokrenuti:
```sh
$ mkdir CORPUS_DIR
$ cp /some/input/samples/* CORPUS_DIR
$ ./my_fuzzer CORPUS_DIR  # -max_len=1000 -jobs=20 ...
```
Novi testovi biće dodavani u direktorijum korpusa.

Podrazumevano ponašanje je da fazer nastavlja da radi beskonačno ili bar
dok greška nije pronađena. Svaki pad ili greška koju detektuje
sanitajzer biće prijavljeni, fazer zaustavljen i test primer koji je
prouzrokovao grešku biće sačuvan u datoteku (obično, `crash-<sha1>`,
`leak-<sha1>` ili `timeout-<sha1>`).

