#include <iostream>

class Fraction
{
    int m_numerator;
    int m_denominator;

  public:
    Fraction(int numerator, int denominator)
    {
        assert(denominator != 0);

        int g = gcd(numerator, denominator);
        m_numerator = numerator / g;
        m_denominator = denominator / g;
    }

    Fraction(const Fraction &copy) = delete;
    Fraction &operator=(const Fraction &f) = delete;

    friend Fraction operator*(const Fraction &f1, const Fraction &f2);
    friend Fraction operator*(int v, const Fraction &f);
    friend Fraction operator*(const Fraction &f, int v);

    friend std::ostream &operator<<(std::ostream &out, const Fraction &f);

  private:
    int gcd(int a, int b)
    {
        return (b == 0) ? (a > 0 ? a : -a) : gcd(b, a % b);
    }
};

std::ostream &operator<<(std::ostream &out, const Fraction &f)
{
    out << f.m_numerator << "/" << f.m_denominator;
    return out;
}

Fraction operator*(const Fraction &f1, const Fraction &f2)
{
    return Fraction(f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator);
}

Fraction operator*(int v, const Fraction &f)
{
    return Fraction(f.m_numerator * v, f.m_denominator);
}

Fraction operator*(const Fraction &f, int v)
{
    return Fraction(f.m_numerator * v, f.m_denominator);
}

int main()
{
    Fraction f1(2, 5);
    std::cout << f1 << std::endl;

    Fraction f2(3, 8);
    std::cout << f2 << std::endl;

    Fraction f3 = f1 * f2;
    std::cout << f3 << std::endl;

    Fraction f4 = f1 * 2;
    std::cout << f4 << std::endl;

    Fraction f5 = 2 * f2;
    std::cout << f5 << std::endl;

    Fraction f6 = Fraction(1, 2) * Fraction(2, 3) * Fraction(3, 4);
    std::cout << f6 << std::endl;
}