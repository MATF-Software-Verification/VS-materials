#ifndef _SORT_H_
#define _SORT_H_ 1

/* Selection sort: Funkcija sortira niz celih brojeva metodom
   sortiranja izborom.  Ideja algoritma je sledeca: U svakoj
   iteraciji pronalazi se najmanji element i premesta se na pocetak
   niza. Dakle, u prvoj iteraciji, pronalazi se najmanji element, i
   dovodi na nulto mesto u nizu. U i-toj iteraciji najmanjih i-1
   elemenata su vec na svojim pozicijama, pa se od elemenata sa
   indeksima od i do n-1 trazi najmanji, koji se dovodi na i-tu
   poziciju. */
void selection_sort(int a[], int n);

/* Insertion sort: Funkcija sortira niz celih brojeva metodom
   sortiranja umetanjem.  Ideja algoritma je sledeca: neka je na
   pocetku i-te iteracije niz prvih i elemenata
   (a[0],a[1],...,a[i-1]) sortirano. U i-toj iteraciji treba
   element a[i] umetnuti na pravu poziciju medju prvih i elemenata
   tako da se dobije niz duzine i+1 koji je sortiran. Ovo se radi
   tako sto se i-ti element najpre uporedi sa njegovim prvim levim
   susedom (a[i-1]). Ako je a[i] vece, tada je on vec na pravom
   mestu, i niz a[0],a[1],...,a[i] je sortiran, pa se moze preci na
   sledecu iteraciju. Ako je a[i-1] vece, tada se zamenjuju a[i] i
   a[i-1], a zatim se proverava da li je potrebno dalje
   potiskivanje elementa u levo, poredeci ga sa njegovim novim
   levim susedom. Ovim uzastopnim premestanjem se a[i] umece na
   pravo mesto u nizu. */
void insertion_sort(int a[], int n);

/* Bubble sort: Funkcija sortira niz celih brojeva metodom
   mehurica. Ideja algoritma je sledeca: prolazi se kroz niz redom
   poredeci susedne elemente, i pri tom ih zamenjujuci ako su u
   pogresnom poretku.  Ovim se najveci element poput mehurica
   istiskuje na "povrsinu", tj. na krajnju desnu poziciju. Nakon
   toga je potrebno ovaj postupak ponoviti nad nizom
   a[0],...,a[n-2], tj. nad prvih n-1 elemenata niza bez poslednjeg
   koji je postavljen na pravu poziciju. Nakon toga se isti
   postupak ponavlja nad sve kracim i kracim prefiksima niza, cime
   se jedan po jedan istiskuju elementi na svoje prave pozicije. */
void bubble_sort(int a[], int n);

/* Selsort: Ovaj algoritam je jednostavno prosirenje sortiranja
   umetanjem koje dopusta direktnu razmenu udaljenih elemenata.
   Prosirenje se sastoji u tome da se kroz algoritam umetanja
   prolazi vise puta. U prvom prolazu, umesto koraka 1 uzima se
   neki korak h koji je manji od n (sto omogucuje razmenu udaljenih
   elemenata) i tako se dobija h-sortiran niz, tj. niz u kome su
   elementi na rastojanju h sortirani, mada susedni elementi to ne
   moraju biti. U drugom prolazu kroz isti algoritam sprovodi se
   isti postupak ali za manji korak h. Sa prolazima se nastavlja
   sve do koraka h = 1, u kome se dobija potpuno sortirani niz.
   Izbor pocetne vrednosti za h, i nacina njegovog smanjivanja
   menja u nekim slucajevima brzinu algoritma, ali bilo koja
   vrednost ce rezultovati ispravnim sortiranjem, pod uslovom da je
   u poslednjoj iteraciji h imalo vrednost 1. */
void shell_sort(int a[], int n);

/* Merge sort: Funkcija sortira niz celih brojeva a[]
   ucesljavanjem. Sortiranje se vrsi od elementa na poziciji l do
   onog na poziciji d. Na pocetku, da bi niz bio kompletno
   sortiran, l mora biti 0, a d je jednako poslednjem validnom
   indeksu u nizu. Funkcija niz podeli na dve polovine, levu i
   desnu, koje zatim rekurzivno sortira. Od ova dva sortirana
   podniza, sortiran niz se dobija ucesljavanjem, tj. istovremenim
   prolaskom kroz oba niza i izborom trenutnog manjeg elementa koji
   se smesta u pomocni niz. Na kraju algoritma, sortirani elementi
   su u pomocnom nizu, koji se kopira u originalni niz. */
void merge_sort(int a[], int l, int d);

/* Quick sort: Funkcija sortira deo niza brojeva a izmedju pozicija
   l i d. Njena ideja sortiranja je izbor jednog elementa niza, koji
   se naziva pivot, i koji se dovodi na svoje mesto. Posle ovog
   koraka, svi elementi levo od njega bice manji, a svi desno bice
   veci od njega. Kako je pivot doveden na svoje mesto, da bi niz
   bio kompletno sortiran, potrebno je sortirati elemente levo
   (manje) od njega, i elemente desno (vece). Kako su dimenzije ova
   dva podniza manje od dimenzije pocetnog niza koji je trebalo
   sortirati, ovaj deo moze se uraditi rekurzivno. */
void quick_sort(int a[], int l, int d);

#endif /*  */
