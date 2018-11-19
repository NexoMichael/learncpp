#include <iostream>

class Average
{
    int32_t sum;
    int8_t count;

  public:
    Average() : sum(0), count(0)
    {
    }

    Average &operator+(int8_t v)
    {
        sum += v;
        count++;
        return *this;
    }

    Average &operator+=(int8_t v)
    {
        sum += v;
        count++;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Average &a);
};

std::ostream &operator<<(std::ostream &out, const Average &a)
{
    out << static_cast<double>(a.sum) / static_cast<double>(a.count);
    return out;
}

int main()
{
    Average avg;

    avg += 4;
    std::cout << avg << '\n'; // 4 / 1 = 4

    avg += 8;
    std::cout << avg << '\n'; // (4 + 8) / 2 = 6

    avg += 24;
    std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

    avg += -10;
    std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

    (avg += 6) += 10;         // 2 calls chained together
    std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

    Average copy = avg;
    std::cout << copy << '\n';

    return 0;
}