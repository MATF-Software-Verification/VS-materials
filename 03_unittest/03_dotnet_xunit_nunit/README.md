## C# (.NET) - xUnit, NUnit

U okviru [.NET ekosistema](https://dotnet.microsoft.com/) postoji bogat skup radnih okvira za testiranje jedinica koda. Neki od njih olakšavaju repetitivno pisanje testova ubrizgavanjem vrednosti u šablone testova (tzv. _teorije_), ili pružaju interfejs za pisanje testova navođenjem ograničenja. Primeri ovakvih radnih okvira koje ćemo razmatrati su [xUnit](https://xunit.net/) i [NUnit](https://nunit.org/). Oba radna okvira podržavaju sve jezike u okviru .NET ekosistema (C#, F#, VB.NET, ...).

### xUnit

Osim jednostavnog interfejsa za pisanje testova nalik na JUnit u programskom jeziku Java, gde se testovi markiraju odgovarajućim anotacijama (što je i slučaj u xUnit radnom okviru markiranjem metoda atributom `[Fact]` [^1]), jedna od najpopularnijih osobina xUnit radnog okvira je mogućnost pisanja _teorija_ - šablona za testove. Umesto da pišemo isti skup pod-testova iznova i iznova za različite podatke (ili umesto da ih izdvajamo u funkcije), možemo zakačiti atribut [^1] `[Theory]`, a unutar atributa `[InlineData]` definisati podatke koji će biti ulaz za test:

[^1]: Atributi u programskom jeziku C# su donekle ekvivalentni anotacijama u programskom jeziku Java. Za razumevanje primera nije neophodno duboko poznavanje koncepta atributa.

```cs
public class ParameterizedTests
{
    public bool SampleAssert1(int a, int b, int c, int d)
    {
        return (a + b) == (c + d);
    }

    public bool SampleAssert2(int a, int b, int c, int d)
    {
        return (a + c) == (b + d);
    }

    // Regular xUnit test case
    // Sub-optimal (repeated asserts)
    [Fact]
    public void SampleFact()
    {
        Assert.True(SampleAssert1(4, 4, 4, 4));
        Assert.True(SampleAssert2(4, 4, 4, 4));

        Assert.True(SampleAssert1(3, 2, 2, 3));
        Assert.True(SampleAssert2(3, 2, 2, 3));
        
        Assert.True(SampleAssert1(7, 0, 0, 7));
        Assert.True(SampleAssert2(7, 0, 0, 7));
        
        Assert.True(SampleAssert1(0, 7, 7, 0));
        Assert.True(SampleAssert2(0, 7, 7, 0));
    }

    // Regular xUnit test case
    // No repeated asserts but requires a local method
    [Fact]
    public void SampleFact()
    {
        PerformAsserts(4, 4, 4, 4);
        PerformAsserts(3, 2, 2, 3);
        PerformAsserts(7, 0, 0, 7);
        PerformAsserts(0, 7, 7, 0);

        void PerformAsserts(int a, int b, int c, int d) 
        {
            Assert.True(SampleAssert1(a, b, c, d));
            Assert.True(SampleAssert2(a, b, c, d));
        }
    }

    // Using Theory and InlineData
    // Optimal solution, replaces above patterns
    [Theory]
    [InlineData(4, 4, 4, 4)]
    [InlineData(3, 2, 2, 3)]
    [InlineData(7, 0, 0, 7)]
    [InlineData(0, 7, 7, 0)]
    public void SampleTheory(int a, int b, int c, int d)
    {
        Assert.True(SampleAssert1(a, b, c, d));
        Assert.True(SampleAssert2(a, b, c, d));
    }

    // There exist special "InlineData" variants, for example "SqlServerData"
    [Theory]
    [SqlServerData("(local)", 
                   "TestDatabase", 
                   "select FirstName, LastName from Users")]
    public void SqlServerTests(string FirstName, string LastName)
    {
        Assert.Equal("Peter Beardsley", $"{FirstName} {LastName}");
    }
}
```

Druga popularna odlika xUnit radnog okvira je jednostavna izolacija test metoda. To se postiže kreiranjem zasebne instance test klase za svaki test metod. Za razliku od drugih popularnih radnih okvira, xUnit ne daje interfejs za markiranje metoda sa ciljem pokretanja tog metoda pre ili posle jednog ili svih testova, već se na osnovu izolacije testova po instanci klase, piše čitljiviji kod koji u konstruktoru i destruktoru klase vrši odgovarajuću pripremu odnosno čišćenje pre odnosno posle pokretanja testova.

Primeri korišćenja xUnit radnog okvira su preuzeti iz zvaničnog repozitorijuma sa primerima i mogu se naći kao git podmodul u okviru repozitorijuma sa materijalima.

### NUnit

Glavna odlika NUnit radnog okvira je model ogranićenja (constraint model). Takav model u radnom okviru pruža samo jedan metod za implementaciju testova. Logika potrebna za testiranje se kodira u objektu ograničenja koji se prosleđuje toj metodi:

```cs
Assert.That(myString, Is.EqualTo("Hello"));
Assert.That(myString, Is.Not.EqualTo("Bello"));
``` 

Primeri korišćenja NUnit radnog okvira su preuzeti iz zvaničnog repozitorijuma sa primerima i mogu se naći kao git podmodul u okviru repozitorijuma sa materijalima.

