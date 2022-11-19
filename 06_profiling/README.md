# Profajliranje

_Profajliranje_ je vrsta dinamičke analize programa (program se analizira tokom izvršavanja) koja se sprovodi kako bi se izmerila, npr. količina memorije koju program zauzima, vreme koje program provodi u određenim funkcijama, iskorišćenost keša itd. Programi koji vrše profajliranje se zovu _profajleri_. Na ovom kursu će biti reči o popularnim profajlerima, njihovim prednosima i manama, uz primere upotrebe.

Profajliranje bi trebalo da nam da jasnu informaciju o tome da li imamo značajna uska grla u kodu. Ako primetimo da neka funkcija uzima 60% vremena izvršavanja, onda je ona glavni kandidat za optimizaciju. Sa druge strane, ako nemamo nijednu funkciju koja troši više od par procenata vremena onda treba pažnju usmeriti na druge pristupe poboljšanja performansi aplikacije (brži hardver, bolja arhitektura/dizajn aplikacije, paralelizacija) ili  ́ce biti potrebno da se optimizuje mnogo koda da bi se napravila ve ́ca razlika. 

Profajleri mogu obezbediti informaciju o tome koliko je vremena potrošeno u svakoj funkciji i u pozivima drugih funkcija, pa i koliko je potrošeno u svakoj liniji koda. Te informacije se, za neke alate kao što su Cachegrind i Callgrind koji generišu izlaz koji ima dosta zajedničkog, mogu prikazati bilo kroz alate koje Valgrind pruža ili kroz specijalizovane alate kao što je _Kcachegrind_.

