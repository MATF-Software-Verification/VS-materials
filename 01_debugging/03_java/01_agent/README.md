## Debagovanje i instrumentovanje Java bajtkoda

### Java agenti

Java agenti su specijalni tip klase koji koristi Java Instrumentation API da modifikuje bajtkod aplikacija koje rade na JVM. Java agenti postoje od ranih verzija Java jezika (tačnije, od verzije 5). Instrumentovanje koda je korisno jer ne zahteva modifikovanje originalnog koda, stoga se agenti mogu "uključiti" u već postojeće aplikacije - to se radi zadavanjem odgovarajućih argumenata u komandnoj liniji prilikom pozivanja aplikacije. Jedan primer agenta može biti i debager - na kraju krajeva, debager treba da posmatra bajtkod i unosi instrukcije za praćenje rada aplikacije, za šta su agenti i namenjeni. Drugi primer upotrebe agenta može biti praćenje pokrivenosti, što je upravo način rada popularnih biblioteka za praćenje pokrivenosti kao npr. [JaCoCo](https://github.com/jacoco/jacoco).

Agent je zapravo normalna Java klasa koja ima specijalni metod `premain`, sa jednim od potpisa:
```java
public static void premain(String agentArgs, Instrumentation inst)
public static void premain(String agentArgs) 
```
Kada se JVM inicijalizuje, poziva `premain` metod svakog priključenog agenta. Nakon što se svi `premain` metodi izvrše, poziva se `main` metod same aplikacije.

Agenti alternativno mogu da imaju metod `agentmain` umesto metoda `premain`, sa jednim od potpisa:
```java
public static void agentmain(String agentArgs, Instrumentation inst) 
public static void agentmain(String agentArgs)
```
Metod `agentmain` se poziva nakon JVM inicijalizacije, i *nakon* pokretanja originalne aplikacije. Agent može imati i `premain` i `agentmain`, ali u tom slučaju će se pozvati samo `premain`.


#### Primer

Kao primer, data je jednostavna Maven aplikacija. Pokrenimo je:
```sh
$ mvn package
[...]
$ java -jar ./prog-test/target/prog-test-0.1-SNAPSHOT.jar
Original method
```

U primeru je dat agent koji modifikuje bajtkod jedne metode date aplikacije. Da bismo priključili agenta, pozovimo opet aplikaciju, ali ovaj put sa dodatnim JVM argumentom `-javaagent`:
```
-javaagent:<putanja_do_agenta>[=<argumenti_agenta>]`
```
Kao putanju prosleđujemo generisani JAR agenta, koji je dobijen kao artifakt izgradnje aplikacije Maven-om. Kao argument prosleđujemo putanju do trenutnog direktorijuma pošto agent treba lokacija klase kako bi promenio njen bajtkod.
```sh
$ java -javaagent:./agent/target/agent-0.1-SNAPSHOT.jar=$PWD -jar ./prog-test/target/prog-test-0.1-SNAPSHOT.jar
Method hacked
```

Vidimo da je agent uspešno modifikovao bajtkod metoda pre izvršavanja aplikacije. Modifikacija je urađena korišćenjem biblioteke [`Javassist`](https://www.javassist.org/).

Agent takođe ima i metod `agentmain`, ali on se ne izvršava jer agent ima i `premain` koji ima veći prioritet.

