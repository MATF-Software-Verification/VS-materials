## gdb

_GNU Debugger_ (gdb) je debager koji se koristi za debagovanje (najčešće) C/C++ programa. Preko gdb je moguće pokrenuti program sa proizvoljnim argumentima komandne linije, posmatrati stanje promenljivih ili registara procesora, pratiti izvršavanje kroz naredbe originalnog ili asembliranog koda, postavljanje bezuslovnih ili uslovnih tačaka prekida i sl. 

Više informacija o gdb debageru se može pročitati [na ovom linku](https://www.sourceware.org/gdb/). 

Iako se gdb-om najčešće debaguju C/C++ programi, nije nemoguće gdb koristiti i u druge svrhe. Moguće je gdb prikačiti na bilo koji pokrenuti proces ili debagovati proizvoljne programe. To uključuje debagovanje `native` funkcija Java virtualne mašine, ili unapred (ahead of time) prevedenih Java/C# programa. Korisno debagovanje svakako zahteva da su debug simboli dostupni (npr. opcija `-g` je prosleđena `gcc` kompilatoru prilikom kompilacije).

