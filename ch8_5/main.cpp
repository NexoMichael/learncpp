#include <iostream>

class Ball
{
    std::string m_color;
    double m_size;

  public:
    Ball(const std::string &color = "black", double size = 10)
        : m_color{color},
          m_size{size}
    {
    }

    Ball(double size) : Ball("black", size)
    {
    }

    void print()
    {
        std::cout << "color: " << m_color << " size: " << m_size << "\n";
    }
};

int main()
{
    Ball def;
    def.print();

    Ball blue("blue");
    blue.print();

    Ball twenty(20.0);
    twenty.print();

    Ball blueTwenty("blue", 20.0);
    blueTwenty.print();

    return 0;
}