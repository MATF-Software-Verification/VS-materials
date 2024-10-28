Console.WriteLine("Hello, World!");
new MyRecord("Hello", 5).MyRecordMethod();

public record MyRecord(string S, int V)
{
    public string MyRecordMethod() => $"{this.S}: {this.V}";
}

