#include <iostream>
#include <vector>
#include <string>

struct StudentGrade
{
    std::string name;
    char grade;
};

class GradeMap
{
    std::vector<StudentGrade> m_map;

  public:
    GradeMap() : m_map({})
    {
    }

    char &operator[](std::string idx)
    {
        for (auto &g : m_map)
            if (g.name == idx)
                return g.grade;

        StudentGrade g{idx, ' '};
        m_map.push_back(g);

        return m_map.back().grade;
    }
};

int main()
{
    GradeMap grades;
    grades["Joe"] = 'A';
    grades["Frank"] = 'B';
    std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
    std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
    return 0;
}