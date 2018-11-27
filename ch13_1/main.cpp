#include <iostream>

template <typename T>
const T &max(const T &a, const T &b)
{
  return (a > b) ? a : b;
}

template <typename T>
T average(T *array, int length)
{
  T sum{0};

  for (int i = 0; i < length; i++)
    sum += array[i];

  return sum / length;
}

class Cents
{
private:
  int m_cents;

public:
  Cents(int cents) : m_cents(cents) {}

  friend std::ostream &operator<<(std::ostream &out, const Cents &c)
  {
    out << "Cents(" << c.m_cents << ")";
    return out;
  }

  friend bool operator>(const Cents &x, const Cents &y)
  {
    return x.m_cents > y.m_cents;
  }

  Cents &operator+=(const Cents &cents)
  {
    m_cents += cents.m_cents;
    return *this;
  }

  Cents &operator/(int d)
  {
    m_cents /= d;
    return *this;
  }
};

int main()
{
  std::cout << max(5, 7) << "\n";

  std::cout << max(1.1, 2.3) << "\n";

  std::cout << max('a', '6') << "\n";

  std::cout << max(Cents(1), Cents(3)) << "\n";

  int array1[] = {1, 2, 3, 4, 5};
  std::cout << average(array1, 5) << "\n";

  double array2[] = {1.1, 2.2, 3.3, 4.4};
  std::cout << average(array2, 4) << "\n";

  Cents array3[] = {Cents(1), Cents(2), Cents(3)};
  std::cout << average(array3, 3) << "\n";

  return 0;
}