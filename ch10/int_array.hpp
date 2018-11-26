#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include <initializer_list>
#include <cassert>

class IntArray
{
  private:
    int m_length;
    int *m_data;

  public:
    IntArray();
    IntArray(int length);
    IntArray(const std::initializer_list<int> &list);
    ~IntArray();

    int &operator[](int index);
    IntArray &operator=(const std::initializer_list<int> &list);
    void erase();
    int getLength();
    void reallocate(int newLength);
    void resize(int newLength);
    void insertBefore(int value, int index);
    void remove(int index);
    void insertAtBeginning(int value);
    void insertAtEnd(int value);
};

#endif // INT_ARRAY_H