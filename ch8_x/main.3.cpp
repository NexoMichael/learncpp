#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

class Monster
{
  public:
    enum MonsterType
    {
        DRAGON,
        GOBLIN,
        OGRE,
        ORC,
        SKELETON,
        TROLL,
        VAMPIRE,
        ZOMBIE,
        MAX_MONSTER_TYPES,
    };

  private:
    MonsterType m_type;
    std::string m_name;
    std::string m_roar;
    int m_hitPoints;

  public:
    Monster(MonsterType type, std::string name, std::string roar, int hitPoints)
        : m_type(type),
          m_name(name),
          m_roar(roar),
          m_hitPoints(hitPoints)
    {
    }

    std::string getTypeString() const
    {
        switch (m_type)
        {
        case DRAGON:
            return "dragon";
        case GOBLIN:
            return "goblin";
        case OGRE:
            return "ogre";
        case ORC:
            return "orc";
        case SKELETON:
            return "skeleton";
        case TROLL:
            return "troll";
        case VAMPIRE:
            return "vampire";
        case ZOMBIE:
            return "zombie";
        default:
            return "???";
        }
    }

    void print();
};

void Monster::print()
{
    std::cout << m_name << " the " << getTypeString() << " has " << m_hitPoints << " hit points and says " << m_roar << "\n";
}

class MonsterGenerator
{
  private:
    static int getRandomNumber(int min, int max)
    {
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
    }

  public:
    static Monster generateMonster();
};

Monster MonsterGenerator::generateMonster()
{
    return Monster(
        static_cast<Monster::MonsterType>(getRandomNumber(0, static_cast<int>(Monster::MAX_MONSTER_TYPES))),
        "Bones",
        "*rattle*",
        getRandomNumber(0, 100));
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();

    Monster m = MonsterGenerator::generateMonster();
    m.print();

    return 0;
}