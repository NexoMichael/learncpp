#include <iostream>
#include <stdexcept>

class Fraction
{
private:
  int m_numerator;
  int m_denominator;

public:
  Fraction(int numerator, int denominator) : m_numerator(numerator), m_denominator(denominator)
  {
    if (denominator == 0)
      throw std::runtime_error("Your fraction has an invalid denominator");
  }

  friend std::ostream &operator<<(std::ostream &out, const Fraction &f);
};

std::ostream &operator<<(std::ostream &out, const Fraction &f)
{
  out << "Fraction: " << f.m_numerator << "/" << f.m_denominator;
  return out;
}

int main()
{
  std::cout << "Enter the numerator: ";
  int numerator;
  std::cin >> numerator;
  std::cin.ignore(32767, '\n');

  std::cout << "Enter the denominator: ";
  int denominator;
  std::cin >> denominator;
  std::cin.ignore(32767, '\n');

  try
  {
    auto f = Fraction(numerator, denominator);
    std::cout << f << std::endl;
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}