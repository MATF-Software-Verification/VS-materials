using Xunit;

namespace CoverageLab.Complete.Tests;

public sealed class DiscountPolicyTests
{
    [Theory]
    [InlineData(100, CustomerKind.Regular, 100)]
    [InlineData(100, CustomerKind.Student, 90)]
    [InlineData(100, CustomerKind.Partner, 85)]
    [InlineData(250, CustomerKind.Regular, 237.50)]
    [InlineData(250, CustomerKind.Student, 212.50)]
    [InlineData(250, CustomerKind.Partner, 200)]
    public void Calculate_returns_discounted_total(decimal subtotal, CustomerKind kind, decimal expected)
    {
        decimal actual = DiscountPolicy.Calculate(subtotal, kind);

        Assert.Equal(expected, actual);
    }

    [Fact]
    public void Calculate_rejects_negative_subtotal()
    {
        Assert.Throws<ArgumentOutOfRangeException>(() =>
            DiscountPolicy.Calculate(-1m, CustomerKind.Regular));
    }
}
