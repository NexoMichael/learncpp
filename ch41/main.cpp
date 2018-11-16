#include <iostream>
#include <utility>

int main()
{
    std::cout << "Enter an integer: ";
    int valueA;
    std::cin >> valueA;

    std::cout << "Enter a larger integer: ";
    int valueB;
    std::cin >> valueB;

    if (valueA > valueB)
        std::swap(valueA, valueB);

    std::cout << "The smaller value is: " << valueA << "\n";
    std::cout << "The larger value is: " << valueB << "\n";
}