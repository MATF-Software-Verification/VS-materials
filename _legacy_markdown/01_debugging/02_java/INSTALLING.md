### Java agenti

Za pokretanje primera su dovoljni [JDK](https://www.oracle.com/java/technologies/downloads/) i [Maven](https://maven.apache.org/).
Na primer, za Ubuntu OS, dovoljno je preuzeti OpenJDK i Maven:
```sh
$ apt-get install default-jdk    # JDK 8, 11, 17, 21 su LTS
$ apt-get install openjdk-17-jdk # alternativno, specificna verzija
$ java -version                  # proveriti instalaciju
$ apt-get install maven
$ mvn -version
```

Za neke alate i skripte je neophodno postaviti `JAVA_HOME` promenljivu okruženja na direktorijum JDK instalacije:
```sh
$ export JAVA_HOME=/path/to/jdk
$ $JAVA_HOME/bin/java -version
```

Obično se `$JAVA_HOME/bin` postavi na `PATH` kako bi se `java*` alati lakše pokretali:
```sh
$ export PATH=$PATH:$JAVA_HOME/bin
$ which java
/path/to/jdk/bin/java
$ java -version
```
