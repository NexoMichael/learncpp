#include <iostream>
#include <vector>

class Shape
{
public:
  virtual std::ostream &print(std::ostream &out) const = 0;
  friend std::ostream &operator<<(std::ostream &out, const Shape &s)
  {
    return s.print(out);
  }
  virtual ~Shape()
  {
    std::cout << "delete Shape: " << this << "\n";
  }
};

class Point
{
private:
  int m_x = 0;
  int m_y = 0;
  int m_z = 0;

public:
  Point(int x, int y, int z) : m_x(x), m_y(y), m_z(z){};

  friend std::ostream &operator<<(std::ostream &out, const Point &p)
  {
    out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
    return out;
  }

  ~Point()
  {
    std::cout << "delete Point: " << this << "\n";
  }
};

class Triangle : public Shape
{
private:
  Point *m_p1;
  Point *m_p2;
  Point *m_p3;

public:
  Triangle(Point *p1, Point *p2, Point *p3) : m_p1(p1), m_p2(p2), m_p3(p3) {}

  virtual std::ostream &print(std::ostream &out) const override
  {
    out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ")";
    return out;
  }

  virtual ~Triangle()
  {
    if (m_p1)
      delete m_p1;
    if (m_p2)
      delete m_p2;
    if (m_p3)
      delete m_p3;

    std::cout << "delete Triangle: " << this << "\n";
  }
};

class Circle : public Shape
{
private:
  Point *m_c;
  int m_r;

public:
  Circle(Point *c, int r) : m_c(c), m_r(r) {}

  virtual std::ostream &print(std::ostream &out) const override
  {
    out << "Circle(" << m_c << ", radius " << m_r << ")";
    return out;
  }

  int getRadius()
  {
    return m_r;
  }

  virtual ~Circle()
  {
    if (m_c)
      delete m_c;
    std::cout << "delete Circle: " << this << "\n";
  }
};

int getLargestRadius(std::vector<Shape *> &v)
{
  int maxRadius{0};

  for (auto const &o : v)
    if (Circle *c = dynamic_cast<Circle *>(o))
      if (c->getRadius() > maxRadius)
        maxRadius = c->getRadius();

  return maxRadius;
}

int main()
{
  std::vector<Shape *> v;
  v.push_back(new Circle(new Point(1, 2, 3), 7));
  v.push_back(new Triangle(new Point(1, 2, 3), new Point(4, 5, 6), new Point(7, 8, 9)));
  v.push_back(new Circle(new Point(4, 5, 6), 3));

  for (auto const &o : v)
    std::cout << *o << std::endl;

  std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

  for (auto const &o : v)
    delete o;

  return 0;
}