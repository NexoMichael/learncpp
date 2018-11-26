#include <iostream>
#include <exception>

struct ZeroDivException : public std::exception
{
    const char *what() const throw()
    {
        return "Division by zero";
    }
};

double division(int x, int y)
{
    if (y == 0)
    {
        throw ZeroDivException();
    }

    return x / y;
}

int main()
{
    int x = 50;
    int y = 0;
    double z;

    try
    {
        z = division(x, y);
        std::cout << z << std::endl;
    }
    catch (ZeroDivException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}