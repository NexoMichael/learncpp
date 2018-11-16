#include <iostream>
#include <utility>

struct Monster
{
    std::string type;
    std::string name;
    int health;
};

void printMonster(Monster m)
{
    std::cout << "This " << m.type << " is named " << m.name << " and has " << m.health << " helath." << std::endl;
}

int main()
{
    Monster torg = {"Ogre", "Torg", 145};
    Monster blurp = {"Slime", "Blurp", 23};

    printMonster(torg);
    printMonster(blurp);
}