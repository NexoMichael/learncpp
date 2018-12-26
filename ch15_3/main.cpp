#include <iostream>

template <class T>
class Auto_ptr3
{
  T *m_ptr;

public:
  Auto_ptr3(T *ptr = nullptr) : m_ptr(ptr)
  {
  }

  ~Auto_ptr3()
  {
    delete m_ptr;
  }

  // // Copy constructor
  // Auto_ptr3(const Auto_ptr3 &a)
  // {
  //   m_ptr = new T;
  //   *m_ptr = *a.m_ptr;
  // }
  Auto_ptr3(const Auto_ptr3 &a) = delete;

  // Move constructor
  Auto_ptr3(Auto_ptr3 &&a) : m_ptr(a.m_ptr)
  {
    a.m_ptr = nullptr;
  }

  // Copy assignment
  // Auto_ptr3 &operator=(const Auto_ptr3 &a)
  // {
  //   if (&a == this)
  //     return *this;

  //   delete m_ptr;

  //   m_ptr = new T;
  //   *m_ptr = *a.m_ptr;

  //   return *this;
  // }
  Auto_ptr3 &operator=(const Auto_ptr3 &a) = delete;

  // Move assignment
  Auto_ptr3 &operator=(Auto_ptr3 &&a)
  {
    if (&a == this)
      return *this;

    delete m_ptr;

    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;

    return *this;
  }

  T &operator*() const { return *m_ptr; }
  T &operator->() const { return m_ptr; }
  bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
  Resource() { std::cout << "Resource allocated\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr3<Resource> generateResource()
{
  Auto_ptr3<Resource> res(new Resource);
  return res;
}

template <class T>
class DynamicArray
{
private:
  unsigned long m_length;
  T *m_array;

public:
  DynamicArray(unsigned long length) : m_length(length), m_array(new T[length])
  {
  }

  ~DynamicArray()
  {
    delete[] m_array;
  }

  // // Copy constructor
  // DynamicArray(const DynamicArray &arr) : m_length(arr.m_length)
  // {
  //   m_array = new T[m_length];
  //   for (unsigned long i = 0; i < m_length; i++)
  //     m_array[i] = arr.m_array[i];
  // }

  // // Copy assignment
  // DynamicArray &operator=(const DynamicArray &arr)
  // {
  //   if (&arr == this)
  //     return *this;

  //   delete[] m_array;

  //   m_length = arr.m_length;
  //   m_array = new T[m_length];
  //   for (unsigned long i = 0; i < m_length; i++)
  //     m_array[i] = arr.m_array[i];

  //   return *this;
  // }

  DynamicArray(const DynamicArray &arr) = delete;
  DynamicArray &operator=(const DynamicArray &arr) = delete;

  // Move constructor
  DynamicArray(DynamicArray &&arr) : m_length(arr.m_length), m_array(arr.m_array)
  {
    arr.m_length = 0;
    arr.m_array = nullptr;
  }

  // Move assignment
  DynamicArray &operator=(DynamicArray &&arr)
  {
    if (&arr == this)
      return *this;

    delete[] m_array;

    m_length = arr.m_length;
    m_array = arr.m_array;
    arr.m_length = 0;
    arr.m_array = nullptr;

    return *this;
  }

  unsigned long getLength() const { return m_length; }
  T &operator[](unsigned long index) { return m_array[index]; }
  const T &operator[](unsigned long index) const { return m_array[index]; }
};

DynamicArray<unsigned long> cloneArrayAndDouble(const DynamicArray<unsigned long> &arr)
{
  DynamicArray<unsigned long> dbl(arr.getLength());
  for (unsigned long i = 0; i < arr.getLength(); i++)
    dbl[i] = arr[i] * 2;
  return dbl;
}

class Timer
{
private:
  using clock_t = std::chrono::high_resolution_clock;
  using second_t = std::chrono::duration<double, std::ratio<1>>;

  std::chrono::time_point<clock_t> m_beg;

public:
  Timer() : m_beg(clock_t::now())
  {
  }

  void reset()
  {
    m_beg = clock_t::now();
  }

  double elapsed() const
  {
    return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
  }
};

int main()
{

  Auto_ptr3<Resource> resource;
  resource = generateResource();

  Timer t;

  DynamicArray<unsigned long> arr{1000000};

  for (unsigned long i = 0; i < arr.getLength(); i++)
    arr[i] = i;

  arr = cloneArrayAndDouble(arr);

  std::cout << t.elapsed() << std::endl;

  return 0;
}