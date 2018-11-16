#include <iostream>
#include <string>
#include <limits>

int main()
{
    std::cout << "Choose 1 or 2:";
    int choice{0};
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter your name:";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "Enter your age:";
    int age;
    std::cin >> age;

    std::cout << "Your name is " << name << " and your age is " << age << ", choice is " << choice << std::endl;

    return 0;
}
