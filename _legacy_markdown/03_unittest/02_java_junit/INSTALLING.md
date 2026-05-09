### Gradle

Da bi se Gradle instalirao, neophodno je na sistemu imati verziju JDK-a veću od 8.  Gradle se potom jednostavno instalira kroz `gradle` za većinu popularnih Linux distribucija. Alternativno, moguće je preuzeti [unapred spremne Gradle artifakte](https://gradle.org/releases) i ručno instalirati Gradle. Primeri pretpostavljaju da je izvršivi fajl (ili alias) `gradle` dostupan na `PATH`-u i pokreće Gradle alat.

Neobavezno za ovaj primer, za laku organizaciju u okruženju sa više različitih JDK verzija, može se koristiti alat [SDKMAN](https://sdkman.io/). Gradle se može instalirati korišćenjem SDKMAN-a: 
```sh
$ sdk install gradle <verzija>
```
Na primer:
```sh
$ sdk install gradle 7.5.1
```
