## Primer rada libFuzzer-a

Primer `fuzz_me.cpp` prevodimo korišćenjem *clang*-a:
```sh
$ clang++  -fsanitize=fuzzer,address fuzz_me.cpp -o fuzz_me
```

Kreiramo direktorijum u koji će nam se čuvati generisani testovi.
```txt
$ mkdir testovi
```

i pokrećemo program:
```
./fuzz_me testovi/
```

Testovi se generišu variranjem postojećih iz direktorijuma testovi
ukoliko ih ima. Novi testovi se dodaju u korpus samo ukoliko povećavaju
pokrivenost kôda nakon svih već ranije generisanih testova. Ukoliko
želimo da nam se generišu testovi samo od ASCII karaktera prilikom
pozivanja programa treba proslediti i opciju `-only_ascii=1`, 0 je
podrazumevana.

```sh
$ ./fuzz_me -only_ascii=1 testovi/
```

Testovi se generišu u direktrijum, nama se prikazuje na ekran sledeći
izlaz:
```txt
INFO: Seed: 2050712183
INFO: Loaded 1 modules (7 guards): [0x77be60, 0x77be7c),
INFO: -max_len is not provided; libFuzzer will not generate inputs larger than 4096 bytes
INFO: A corpus is not provided, starting from an empty corpus
#0      READ units: 1
#2      INITED cov: 3 ft: 3 corp: 1/1b exec/s: 0 rss: 30Mb
#5      NEW    cov: 4 ft: 4 corp: 2/4b exec/s: 0 rss: 31Mb L: 3 MS: 3 CopyPart-ChangeBit-InsertByte-
#1114   NEW    cov: 5 ft: 5 corp: 3/122b exec/s: 0 rss: 33Mb L: 118 MS: 2 ShuffleBytes-InsertRepeatedBytes-
#176228 NEW    cov: 6 ft: 6 corp: 4/242b exec/s: 0 rss: 235Mb L: 120 MS: 1 CMP- DE: "U\x00"-
#555573 NEW    cov: 7 ft: 7 corp: 5/366b exec/s: 555573 rss: 401Mb L: 124 MS: 1 CMP- DE: "Z\x00\x00\x00"-
#1048576        pulse  cov: 7 ft: 7 corp: 5/366b exec/s: 524288 rss: 409Mb
#2097152        pulse  cov: 7 ft: 7 corp: 5/366b exec/s: 419430 rss: 409Mb
=================================================================
==26069==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000023bb3 at pc 0x000000539e73 bp 0x7fff6c301bc0 sp 0x7fff6c301bb8
READ of size 1 at 0x602000023bb3 thread T0
.....
==26069==ABORTING
MS: 2 ChangeBinInt-CrossOver-; base unit: 1162a64ba4eb59dab49cfb3a8bb87abe708c3bb1
0x46,0x55,0x5a,
FUZ
artifact_prefix='./'; Test unit written to ./crash-0eb8e4ed029b774d80f2b66408203801cb982a60
Base64: RlVa
```

Opcijom `-max-len=N` možemo postaviti maksimalnu dužinu ulaza na neku
drugu veličinu. Poruku
`INFO: A corpus is not provided, starting from an empty corpus` označava
da smo počeli sa praznim korpusom, kao što i jesmo. `READ` prati broj
pročitanih testova iz korpusa, svaki novo dodati test je obelezen sa
`NEW`. Broj na početku linije predstavlja redni broj generisanog testa.
Ako je `NEW` u nastavku onda je i dodat u korpus, ako stoji `pulse`,
tada je taj red ispisan samo zbog programera da bude obavešten da fuzzer
i dalje radi. Vidimo da je fuzzer generisao 2097152 testova pre nego što
je naišao na greku koja mu je prekinula rad. Dogodilo se prekoračenje
memorije na hipu i generisan nam je izveštaj o prekidu rada
`./crash-0eb8e4ed029b774d80f2b66408203801cb982a60` sa sve ulazom koji je
grešku izazvao `FUZ`.

Pojašnjenje kôdova događaja i prateće statistike:
- `READ` - Fuzzer je pročitao sve od datih testova iz direktorijuma sa
    korpusima.

- `INITED` - Fuzzer je završio inicijalizaciju, što uključuje izvršavanje svakog inicijalnog testa kroz kôd koji se testira.

- `NEW` - Fuzzer je kreirao nov test koji pokriva do sad ne pokrivene delove kôda koji se testira. Ovaj test će biti sačuvan u direktorijumu glavnog korpusa.

- `REDUCE` - Fuzzer je pronašao bolji (kraći) test koji izaziva prethodno otkriveno ponašanje. Može se isključiti opcijom `-reduce_inputs=0`.

- `pulse` - Fuzzer je generisao `2n` testotva. Poruka se generiše periodično da bi se korisnik uverio da fuzzer i dalje radi.

- `DONE` - Fuzzer je završio sa radom jer je došao da limita broja iteracija (zadaje se opcijom `-runs`) ili vremenskog limita (zadaje se opcijom `-max_total_time`).

- `RELOAD` - Fuzzer periodično ponovno učitava testove iz direktorijuma sa korpusom. Ovo omogućava fuzzeru da uzme u obzir testove koji su
otkriveni drugim procesima fuzzera, prilikom paralelnog fuzz testiranja.

Svaka izlazna linija sadrži i izveštaj sa sledećim statistikama, kada
nisu 0:

- `cov:` Ukupan broj blokova kôda ili ivica pokrivenih izvršavanjem trenutnog korpusa.

- `ft:` *libFuzzer* koristi različite signale da proceni pokrivenost kôda: pokrivenost ivica, brojače ivica, profajleri vrednosti, indirektne parove pozivaoc/pozvani, itd. Ovi signali su kombinovani i obeleženi sa `(ft:)`.

- `corp:` Broj testova u trenutnom korpusu u memoriji i njegova veličina u B.

- `lim:` Trenutni limit u dužini novih ulaznih podataka u korpusu. Povećava se tokom vremena, dok ne dostigne maksimalnu dužinu. Ona se može zadati opcijom `-max_len`.

- `exec/s:` Broj iteracija fuzzera u sekundi.

- `rss:` Trenutno iskorišćeno memorije.

Za nove (NEW) događaje, izlazna linija sadrži i informacije:

- `L:` Veličina novog testa u bajtovima.

- `MS: <n> <ops>` Broj i lista operacija mutacija koje su korišćene da bi se generisao nov ulaz.

