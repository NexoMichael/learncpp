#include <iostream>

int getIntValue()
{
    std::cout << "Enter integer value: ";
    int result;
    do
    {
        std::cin >> result;
        if (std::cin.fail())
            std::cin.clear();
        std::cin.ignore(32767, '\n');
        if (result <= 0)
            std::cout << "Invalid input. Try again: ";
    } while (result <= 0);

    return result;
}

char getOpValue()
{
    std::cout << "Enter one of: +, -, * , /: ";
    char result;
    do
    {
        std::cin >> result;
        if (std::cin.fail())
            std::cin.clear();
        std::cin.ignore(32767, '\n');
        if (result != '+' && result != '-' && result != '/' && result != '*')
            std::cout << "Invalid input. Try again: ";
    } while (result != '+' && result != '-' && result != '/' && result != '*');

    return result;
}

int add(int a, int b)
{
    return a + b;
}
int subtract(int a, int b)
{
    return a - b;
}
int multiply(int a, int b)
{
    return a * b;
}
int divide(int a, int b)
{
    return a / b;
}

typedef int (*arithmeticFcn)(int, int);

struct arithmeticStruct
{
    char op;
    arithmeticFcn fcn;
};

static const arithmeticStruct ops[]{
    {'+', add},
    {'-', subtract},
    {'*', multiply},
    {'/', divide},
};

arithmeticFcn getArithmeticFunction(char c)
{
    for (const auto &op : ops)
    {
        if (op.op != c)
            continue;
        return op.fcn;
    }
    return nullptr;
}

int main()
{
    int a = getIntValue();
    char op = getOpValue();
    int b = getIntValue();

    int result = getArithmeticFunction(op)(a, b);

    std::cout
        << a << op << b << "=" << result;
    return 0;
}