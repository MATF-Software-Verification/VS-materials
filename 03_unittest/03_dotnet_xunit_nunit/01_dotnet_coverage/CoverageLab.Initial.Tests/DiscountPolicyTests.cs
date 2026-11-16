using Xunit;

namespace CoverageLab.Initial.Tests;

public sealed class DiscountPolicyTests
{
    [Theory]
    [InlineData(100, CustomerKind.Regular, 100)]
    [InlineData(100, CustomerKind.Student, 90)]
    [InlineData(250, CustomerKind.Student, 212.50)]
    public void Calculate_returns_discounted_total(decimal subtotal, CustomerKind kind, decimal expected)
    {
        decimal actual = DiscountPolicy.Calculate(subtotal, kind);

        Assert.Equal(expected, actual);
    }
}
