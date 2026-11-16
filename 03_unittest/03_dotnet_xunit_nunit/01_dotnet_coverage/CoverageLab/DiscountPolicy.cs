namespace CoverageLab;

public static class DiscountPolicy
{
    public static decimal Calculate(decimal subtotal, CustomerKind kind)
    {
        if (subtotal < 0m)
        {
            throw new ArgumentOutOfRangeException(nameof(subtotal), "Subtotal must be non-negative.");
        }

        decimal discountRate = kind switch
        {
            CustomerKind.Student => 0.10m,
            CustomerKind.Partner => 0.15m,
            _ => 0m
        };

        if (subtotal >= 200m)
        {
            discountRate += 0.05m;
        }

        decimal discount = decimal.Round(subtotal * discountRate, 2, MidpointRounding.AwayFromZero);
        return subtotal - discount;
    }
}
