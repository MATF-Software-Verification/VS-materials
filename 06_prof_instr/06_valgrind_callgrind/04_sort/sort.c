#include "sort.h"

#define MAX 1000000
void selection_sort(int a[], int n) {
    int i, j;
    int min;
    int pom;

    /* U svakoj iteraciji ove petlje pronalazi se najmanji element
       medju elementima a[i], a[i+1],...,a[n-1], i postavlja se na
       poziciju i, dok se element na pozciji i premesta na poziciju
       min, na kojoj se nalazio najmanji od navedenih elemenata. */
    for (i = 0; i < n - 1; i++) {

        /* Unutrasnja petlja pronalazi poziciju min, na kojoj se nalazi
           najmanji od elemenata a[i],...,a[n-1]. */
        min = i;
        for (j = i + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;

        /* Zamena elemenata na pozicijama (i) i min. Ovo se radi samo
           ako su (i) i min razliciti, inace je nepotrebno. */
        if (min != i) {
            pom = a[i];
            a[i] = a[min];
            a[min] = pom;
        }
    }
}
void insertion_sort(int a[], int n) {
    int i, j;

    /* Na pocetku iteracije pretpostavlja se da je niz
       a[0],...,a[i-1] sortiran */
    for (i = 1; i < n; i++) {

        /* U ovoj petlji se redom potiskuje element a[i] ulevo koliko
           je potrebno, dok ne zauzme pravo mesto, tako da niz
           a[0],...a[i] bude sortiran. Indeks j je trenutna pozicija na
           kojoj se element koji se umece nalazi. Petlja se zavrsava
           ili kada element dodje do levog kraja (j==0) ili kada se
           naidje na element a[j-1] koji je manji od a[j]. */
        int temp = a[i];
        for (j = i; j > 0 && temp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = temp;
    }
}
void bubble_sort(int a[], int n) {
    int i, j;
    int ind;
    for (i = n, ind = 1; i > 1 && ind; i--)

        /* Poput "mehurica" potiskuje se najveci element medju
           elementima od a[0] do a[i-1] na poziciju i-1 uporedjujuci
           susedne elemente niza i potiskujuci veci u desno */
        for (j = 0, ind = 0; j < i - 1; j++)
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                /* Promenljiva ind registruje da je bilo premestanja. Samo
                   u tom slucaju ima smisla ici na sledecu iteraciju, jer
                   ako nije bilo premestanja, znaci da su svi elementi vec
                   u dobrom poretku, pa nema potrebe prelaziti na kraci
                   prefiks niza. Algoritam bi bio korektan i bez ovoga.
                   Sortiranje bi bilo ispravno, ali manje efikasno, jer bi
                   se cesto nepotrebno vrsila mnoga uporedjivanja, kada je
                   vec jasno da je sortiranje zavrseno. */
                ind = 1;
            }
}
void shell_sort(int a[], int n) {
    int h = n / 2, i, j;

    while (h > 0) {

        /* Insertion sort sa korakom h */
        for (i = h; i < n; i++) {
            int temp = a[i];
            j = i;
            while (j >= h && a[j - h] > temp) {
                a[j] = a[j - h];
                j -= h;
            }
            a[j] = temp;
        }
        h = h / 2;
    }
}
void merge_sort(int a[], int l, int d) {
    int s;
    static int b[MAX]; /* Pomocni niz */
    int i, j, k;

    /* Izlaz iz rekurzije */
    if (l >= d)
        return;

    /* Odredjivanje sredisnjeg indeksa */
    s = (l + d) / 2;

    /* Rekurzivni pozivi */
    merge_sort(a, l, s);
    merge_sort(a, s + 1, d);

    /* Inicijalizacija indeksa. Indeks i prolazi krozi levu polovinu
       niza, dok indeks j prolazi kroz desnu polovinu niza. Indeks k
       prolazi kroz pomocni niz b[] */
    i = l;
    j = s + 1;
    k = 0;

    /* "Ucesljavanje" koriscenjem pomocnog niza b[] */
    while (i <= s && j <= d) {
        if (a[i] < a[j])
            b[k++] = a[i++];

        else
            b[k++] = a[j++];
    }

    /* U slucaju da se prethodna petlja zavrsila izlaskom promenljive
       j iz dopustenog opsega u pomocni niz se prepisuje ostatak leve
       polovine niza */
    while (i <= s)
        b[k++] = a[i++];

    /* U slucaju da se prethodna petlja zavrsila izlaskom promenljive
       i iz dopustenog opsega u pomocni niz se prepisuje ostatak desne
       polovine niza */
    while (j <= d)
        b[k++] = a[j++];

    /* Prepisuje se "ucesljani" niz u originalni niz */
    for (k = 0, i = l; i <= d; i++, k++)
        a[i] = b[k];
}

/* Pomocna funkcija koja menja mesto i-tom i j-tom elementu niza a */
void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
void quick_sort(int a[], int l, int d) {
    int i, pivot_pozicija;

    /* Izlaz iz rekurzije -- prazan niz */
    if (l >= d)
        return;

    /* Particionisanje niza. Svi elementi na pozicijama levo od
       pivot_pozicija (izuzev same pozicije l) su strogo manji od
       pivota. Kada se pronadje neki element manji od pivota, uvecava
       se promenljiva pivot_pozicija i na tu poziciju se premesta
       nadjeni element. Na kraju ce pivot_pozicija zaista biti
       pozicija na koju treba smestiti pivot, jer ce svi elementi levo
       od te pozicije biti manji a desno biti veci ili jednaki od
       pivota. */
    pivot_pozicija = l;
    for (i = l + 1; i <= d; i++)
        if (a[i] < a[l])
            swap(a, ++pivot_pozicija, i);

    /* Postavljanje pivota na svoje mesto */
    swap(a, l, pivot_pozicija);

    /* Rekurzivno sortiranje elementa manjih od pivota */
    quick_sort(a, l, pivot_pozicija - 1);

    /* Rekurzivno sortiranje elementa vecih od pivota */
    quick_sort(a, pivot_pozicija + 1, d);
}
