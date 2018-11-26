#include "int_array.hpp"
#include <initializer_list>
#include <cassert>

IntArray::IntArray() : m_length(0), m_data(nullptr)
{
}

IntArray::IntArray(int length) : m_length(length)
{
    assert(length >= 0);

    if (length > 0)
        m_data = new int[static_cast<unsigned long>(length)];
    else
        m_data = nullptr;

    m_length = length;
}

IntArray::IntArray(const std::initializer_list<int> &list) : IntArray(list.size())
{
    int count = 0;
    for (auto &el : list)
        m_data[count++] = el;
}

IntArray::~IntArray()
{
    delete m_data;
}

int &IntArray::operator[](int index)
{
    assert(index >= 0 && index < m_length);
    return m_data[index];
}

IntArray &IntArray::IntArray::operator=(const std::initializer_list<int> &list)
{
    (*this).reallocate(list.size());

    int count = 0;
    for (auto &el : list)
        m_data[count++] = el;

    return *this;
}

void IntArray::erase()
{
    delete m_data;

    m_length = 0;
    m_data = nullptr;
}

int IntArray::getLength()
{
    return m_length;
}

void IntArray::reallocate(int newLength)
{
    assert(newLength >= 0);

    delete m_data;
    if (newLength > 0)
        m_data = new int[static_cast<unsigned long>(newLength)];
    else
        m_data = nullptr;
    m_length = newLength;
}

void IntArray::resize(int newLength)
{
    if (newLength == m_length)
        return;

    if (newLength <= 0)
    {
        erase();
        return;
    }

    int *data = new int[static_cast<unsigned long>(newLength)];
    if (m_length > 0)
    {
        int itemsToCopy = (m_length < newLength) ? m_length : newLength;
        for (int i = 0; i < itemsToCopy; ++i)
            data[i] = m_data[i];
    }

    delete m_data;
    m_data = data;
    m_length = newLength;
}

void IntArray::insertBefore(int value, int index)
{
    assert(index >= 0 && index <= m_length);

    int *data = new int[static_cast<unsigned long>(m_length + 1)];

    for (int i = 0; i < index; i++)
        data[i] = m_data[i];

    data[index] = value;

    for (int i = index; i < m_length; i++)
        data[i + 1] = m_data[i];

    delete m_data;
    m_data = data;
    m_length++;
}

void IntArray::remove(int index)
{
    assert(index >= 0 && index < m_length);

    if (m_length == 1)
    {
        erase();
        return;
    }
    int *data = new int[static_cast<unsigned long>(m_length - 1)];

    for (int i = 0; i < index; i++)
        data[i] = m_data[i];
    for (int i = index + 1; i < m_length; i++)
        data[i - 1] = m_data[i];

    delete m_data;
    m_data = data;
    m_length--;
}

void IntArray::insertAtBeginning(int value)
{
    insertBefore(value, 0);
}
void IntArray::insertAtEnd(int value)
{
    insertBefore(value, m_length);
}