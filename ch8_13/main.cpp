#include <iostream>

class Vector3d
{
  private:
    double m_x, m_y, m_z;

  public:
    Vector3d(double x = 0.0, double y = 0.0, double z = 0.0)
        : m_x(x), m_y(y), m_z(z)
    {
    }

    void print()
    {
        std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
    }
};

class Point3d
{
  private:
    double m_x, m_y, m_z;

  public:
    Point3d(double x = 0.0, double y = 0.0, double z = 0.0)
        : m_x(x), m_y(y), m_z(z)
    {
    }

    void print()
    {
        std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n";
    }

    void moveByVector(const Vector3d &v)
    {
        // implement this function as a friend of class Vector3d
    }
};

int main()
{
    Point3d p(1.0, 2.0, 3.0);
    Vector3d v(2.0, 2.0, -3.0);

    p.print();
    p.moveByVector(v);
    p.print();

    return 0;
}