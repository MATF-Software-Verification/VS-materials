# Jezici za programiranje i formalnu verifikaciju (Dafny)

[Dafny](https://dafny.org/) je programski jezik sa podrškom za pisanje specifikacija i formalno verifikovanje programa, opremljen statičkim verifikatorom programa. Uklapanjem sofisticiranog automatizovanog rezonovanja sa poznatim programerskim idiomima i alatima, Dafny omogućava programerima da pišu kod koji se može formalno verifikovati uzimajući u obzir navedene specifikacije. Dafny programe je moguće prevesti u C#, Java, JavaScript i Go, i tako integrisati Dafny u postojeće projekte.

## Pisanje Dafny programa

Dafny program (ekstenzije `.dfy`) predstavlja skup deklaracija. Deklaracije uvode _tipove_, _metode_ i _funkcije_ (redosled deklaracija je nebitan). Tipovi mogu biti _klase_ i _induktivni tipovi_. Klase takođe mogu sadržati skup deklaracija _polja_, _metoda_ i _funkcija_. Ukoliko program sadrži definiciju metoda `Main` bez parametara, onda će to biti ulazna tačka programa, međutim nije neophodno da program ima `Main` metod da bi bio verifikovan.

### Polja

Unutar klase, polje se definiše na sledeći način:
```cs
var x: T
```

Tip `T` je neophodno navesti (neće biti dedukovan). Polja je dodatno moguće kvalifikovati ključnom rečju `ghost` koja označava da se to polje koristi samo unutar specifikacija. 

Tipovi podataka u Dafny jeziku:
- `bool` - istinitosni tip
- `int` - neograničeni ceo broj
- `nat` - podskup tipa `int`, predstavlja nenegativne cele brojeve
- `string` - niske
- `set<T>` - konačni imutabilni set vrednosti tipa `T`
- `seq<T>` - imutabilna sekvenca vrednosti tipa `T`
- `array<T>`, `array2<T>`, `array3<T>` ... `arrayN<T>` - nizovni tipovi dimenzije `N`
- `object` - nadtip svih klasnih tipova

## Metode

Deklaracija metoda ima sledeći oblik:
```cs
method M(a: A, b: B, c: C) returns (x: X, y: Y, z: Y)
  requires Pre
  modifies Frame
  ensures Post
  decreases TerminationMetric
{
  Body
}
```
gde su:
- `a`, `b` i `c` ulazni parametri metoda (metodi unutar klase imaju implicitni ulazni parametar `this`)
- `x`, `y` i `z` izlazni parametri metoda
- `Pre` istinitosni izraz koji predstavlja preduslov metoda 
- `Frame` skup objekata čija polja mogu biti ažurirana pozivom metoda; može biti lista izraza gde svaki izraz može biti objekat ili skup objekata (uključujući i `this` ukoliko je metod deklarisan unutar klase) - `Frame` metoda je unija takvih listi i objekata alociranih unutar tela metoda
- `Post` istinitosni izraz koji predstavlja postuslov metoda
- `TerminationMetric` funkcija varijanta metoda 
- `Body` implementacija metoda

Podrazumevano, uslovi imaju vrednost `true` dok je `Frame` prazan skup. Ukoliko nije navedena, Dafny će pokušati da dedukuje funkciju varijantu metoda. 

Metode se mogu koristiti kao leme navođenjem ključne reči `lemma` umesto `method`.

## Funkcije

Primer definicije funkcije:
```cs
function F(a: A, b: B, c: C): T
  requires Pre
  reads Frame
  ensures Post
  decreases TerminationMetric
{
  Body
}
```

Preduslov omogućava funkciji da bude definisana uslovno - Dafny će verifikovati da preduslov važi prilikom svakog poziva funkcije. Postuslov može biti dobro mesto za navođenje svojstava funkcije koja zahtevaju induktivni dokaz.

Na primer, definicija ispod navodi postuslov da je rezultat rada funkcije uvek pozitivan (funkcija referiše na samu sebe u postuslovu):
```cs
function Factorial(n: int): int
  requires 0 <= n
  ensures 1 <= Factorial(n)
{
  if n == 0 then 1 else Factorial(n-1) * n
}
```

Podrazumevano, funkcije su duhovi (`ghost`), dakle ne mogu se pozvati iz koda koji se izvršava. Ovo ponašanje se može pregaziti definisanjem funkcije kao `function method`. Specijalno, funkcije koje imaju povratnu vrednost `bool` se mogu deklarisati navođenjem ključne reči `predicate` umesto `function`.

## Induktivni tipovi

Induktivni tipovi su tipovi čije se vrednosti kreiraju iz fiksiranog skupa konstruktora. Na primer:
```cs
datatype Tree = Leaf | Node(Tree, int, Tree)

// moguce je definisati imena parametara konstruktora
datatype Tree = Leaf | Node(left: Tree, data: int, right: Tree)
```

Za svaki konstruktor `Ct` se implicitno deklariše i član `Ct?` koji vraća `true` ako je objekat konstruisan korišćenjem konstruktora `Ct`. Na primer:
```cs
var t0 := Leaf; 
var t1 := Node(t0, 5, t0);
t1.Node?    // true
t0.Node?    // false
```

## Naredbe

```cs
var LocalVariables := ExprList;

Lvalues := ExprList;

assert BoolExpr;

print ExprList;

if BoolExpr0 {
    Stmts0
} else if BoolExpr1 {
    Stmts1
} else {
    Stmts2
}

while BoolExpr
    invariant Inv
    modifies Frame
    decreases Rank
{
    Stmts
}

match Expr {
    case Empty => Stmts0
    case Node(l, d, r) => Stmts1
}

break;

return;
```

## Izrazi

Izrazi u Dafny jeziku su slični izrazima u C sintaksi, sa malim izmenama/dodacima:
- `==>` operator implikacije
- `<==>` ako-i-samo-ako operator
- poređenja se mogu ulančavati: `0 <= i < j <= a.Length == N`
- `%` uvek vraća nenegativan broj
- prisutni su kvantifikatori:
    -  `forall x :: Expr`
    - `exists x :: Expr`
- operacije nad skupovima: 
    - `+` (unija) 
    - `*` (presek)
    - `-` (razlika)
    - `<` (pravi podskup)
    - `<=` (podskup)
    - `>` (pravi nadskup)
    - `>=` (nadskup)
    - `!!` (razdvojenost skupova)
    - `in` i `!in` ((ne)pripadnost skupu, npr. `x !in S`)
    - `{}` (konstrukcija skupa, npr: `{x,y}`)
- operacije nad sekvencama:
    - `+` (konkatenacija)
    - `<` (pravi prefiks)
    - `<` (prefiks)
    - `in` i `!in` ((ne)pripadnost sekvenci, npr. `x !in S`)
    - `||` (dužina sekvence, npr. `|S|`)
    - `[]` (`0`-indeksiranje sekvence, npr. `S[i]`)
    - `[..]` (sečenje sekvence, npr. `S[1..10]`, desni kraj se ne uključuje)

