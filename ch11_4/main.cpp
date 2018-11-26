#include <iostream>
#include <string>

class Fruit
{
  protected:
    std::string m_name;
    std::string m_color;

  public:
    Fruit(std::string name, std::string color) : m_name(name), m_color(color)
    {
    }
};

class Apple : public Fruit
{
  private:
    double m_fiber;

  public:
    Apple(std::string name, std::string color, double fiber) : Fruit(name, color), m_fiber(fiber)
    {
    }

    friend std::ostream &operator<<(std::ostream &out, const Apple &a);
};

class Banana : public Fruit
{
  public:
    Banana(std::string name, std::string color) : Fruit(name, color)
    {
    }

    friend std::ostream &operator<<(std::ostream &out, const Banana &a);
};

std::ostream &operator<<(std::ostream &out, const Apple &a)
{
    out << "Apple(" << a.m_name << ", " << a.m_color << ", " << a.m_fiber << ")\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Banana &b)
{
    out << "Banana(" << b.m_name << ", " << b.m_color << ")\n";
    return out;
}

int main()
{
    const Apple a("Red delicious", "red", 4.2);
    std::cout << a;

    const Banana b("Cavendish", "yellow");
    std::cout << b;

    return 0;
}