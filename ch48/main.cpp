#include <iostream>
#include <utility>

enum class MonsterType
{
    OGRE,
    DRAGON,
    ORC,
    GIANT,
    SLIME,
};

std::string mosterTypeToString(MonsterType t)
{
    switch (t)
    {
    case MonsterType::OGRE:
        return "Ogre";
    case MonsterType::DRAGON:
        return "Dragon";
    case MonsterType::ORC:
        return "Orc";
    case MonsterType::GIANT:
        return "Giant";
    case MonsterType::SLIME:
        return "Slime";
    }
    return "Unknown";
}

struct Monster
{
    MonsterType type;
    std::string name;
    int health;
};

void printMonster(Monster m)
{
    std::cout
        << "This " << mosterTypeToString(m.type)
        << " is named " << m.name
        << " and has " << m.health
        << " helath." << std::endl;
}

int main()
{
    Monster torg = {MonsterType::OGRE, "Torg", 145};
    Monster blurp = {MonsterType::SLIME, "Blurp", 23};

    printMonster(torg);
    printMonster(blurp);
}