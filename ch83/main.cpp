#include <iostream>
#include <array>

class Stack
{
    std::array<int, 10> stack;
    size_t size;

  public:
    void reset();
    void push(int v);
    void print();
    void pop();
};

void Stack::reset()
{
    stack.empty();
    size = 0;
}

void Stack::print()
{
    std::cout << "( ";
    for (size_t i = 0; i < size; i++)
        std::cout << stack.at(i) << " ";
    std::cout << ")\n";
}

void Stack::push(int v)
{
    if (size < stack.size())
        stack[size++] = v;
}

void Stack::pop()
{
    if (size > 0)
        size--;
}

int main()
{
    Stack stack;
    stack.reset();

    stack.print();

    stack.push(5);
    stack.push(3);
    stack.push(8);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();

    stack.print();

    return 0;
}