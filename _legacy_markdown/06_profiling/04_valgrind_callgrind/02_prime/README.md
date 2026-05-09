#### Primer: Prosti brojevi

Program koristi ne tako jeftinu bibliotečku funkciju `sqrt`.
- Izmeniti funkciju tako da se ne koristi promenljiva limit već da se u uslov for petlje stavi poziv funkcije `sqrt`. Kako to utiče na broj instrukcija programa?
- Izmenom programa da umesto upotrebe `sqrt` imamo u petlji izlazak ukoliko `i*i > x` stvari se ne popravljaju. Funkcija se poziva 1000000 puta i pre svake naredne iteracije petlje proverava se uslov ostanka u petlji. Koliko god da je brže množenje od korenovanja, pomnoženo sa nekoliko miliona, čak ima i veći broj instrukcija nego funkcija koja koristi korenovanje.
- Izmeniti uslov petlje na `i < x/2`. Izmeniti petlju tako da se pre petlje proverava za parne brojeve, a posle u petlji da se iterira samo po neparnim brojevima.
- Sklopiti najefikasniju implementaciju.
