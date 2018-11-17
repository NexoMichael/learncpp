#include <iostream>

double getDouble()
{
    while (1)
    {
        std::cout << "Enter double value: ";
        double x;
        std::cin >> x;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
        }
        else
        {
            std::cin.ignore(32767, '\n');
            return x;
        }
    }
}

double getOperator()
{
    while (1)
    {
        std::cout << "Enter one of the following: +, -, * or /: ";
        char op;
        std::cin >> op;

        std::cin.ignore(32767, '\n');
        if (op == '+' || op == '-' || op == '*' || op == '/')
            return op;
        else
            std::cout << "Oops. Invalid operator" << std::endl;
    }
}

void printResult(double x, char op, double y)
{
    switch (op)
    {
    case '+':
        std::cout << x << " + " << y << " = " << x + y << std::endl;
        break;
    case '-':
        std::cout << x << " - " << y << " = " << x - y << std::endl;
        break;
    case '*':
        std::cout << x << " * " << y << " = " << x * y << std::endl;
        break;
    case '/':
        std::cout << x << " / " << y << " = " << x / y << std::endl;
        break;
    default:
        std::cout << "Oops. Invalid operator" << std::endl;
    }
}

int main()
{
    double x = getDouble();
    char op = getOperator();
    double y = getDouble();

    printResult(x, op, y);

    return 0;
}