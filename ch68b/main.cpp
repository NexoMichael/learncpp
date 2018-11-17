#include <iostream>

int main()
{
    char name1[] = "Bob";
    std::cout << name1;

    const char *name2 = "Alex";
    std::cout << name2;

    return 0;
}