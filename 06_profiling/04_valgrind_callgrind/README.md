### Callgrind

Callgrind je alat koji generiše listu poziva funkcija korisničkog programa u vidu grafa. U osnovnim podešavanjima sakupljeni podaci sastoje se od broja izvršenih instrukcija, njihov odnos sa linijom u izvršnom kodu, odnos pozivaoc/pozvan izmedu funkcija, kao i broj takvih poziva.

Podaci koji se analiziraju i nakon završetka rada programa i alata zapisuju u datoteku `callgrind.out.<pid>`, gde `<pid>` predstavlja identifikator procesa. Program `callgrind_annotate` na osnovu generisanog izveštaja prikazuje listu funkcija. Za grafičku vizuelizaciju preporučeno je koristiti alate kao npr. KCachegrind, koji olakšava navigaciju ukoliko Callgrind napravi veliku količinu podataka.

Program `callgrind_control` omogućava interaktivnu kontrolu i  nadgledanje programa prilikom izvršavanja. Mogu se dobiti informacije o stanju na steku, može se takode u svakom trenutku generisati profil.

Alat Cachegrind sakuplja podatke, odnosno broji dogadaje koji se dešavaju direktno u jednoj funkciji. Ovaj mehanizam sakupljanja podataka se naziva ekskluzivnim. Ovu funkcionalnost proširuje tako što propagira cenu funkcije preko njenih granica. Na primer, ako funkcija `foo` poziva funkciju `bar`, cena funkcije `bar` se dodaje funkciji `foo`. Kada se ovaj mehanizam primeni na celu funkciju, dobija se slika takozvanih inkluzivnih poziva, gde cena svake funkcije uključuje i cene svih funkcija koje ona poziva, direktno ili indirektno.

Zahvaljujući grafu poziva, može da se odredi, počevši od `main` funkcije, koja funkcija ima najveću cenu poziva. Pozivaoc/pozvan cena je izuzetno korisna za profilisanje funkcija koje imaju više poziva iz raznih funkcija, i gde imamo priliku optimizacije našeg programa menjajući kod u funkciji koja je pozivaoc, tačnije redukovanjem broja poziva.

Dodatno može da vrši analizu upotrebe keš memorije i profajliranje grana programa slično kao kod Cachegrind-a. Za takvo profajliranje potrebno je uključiti opcije `--cache-sim=yes` i `--branch-sim=yes`. Stoga Callgrind možemo smatrati i proširenjem Cachegrind -a.
