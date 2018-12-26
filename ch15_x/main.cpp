#include <iostream>
#include <memory> // for std::shared_ptr

class Resource
{
  public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main_3a()
{
    auto ptr1 = std::make_shared<Resource>();
    auto ptr2{ptr1};

    return 0;
}

// class Something; // assume Something is a class that can throw an exception

// int main_3b()
// {
//     auto a = std::make_shared<Something>();
//     doSomething(a, std::shared_ptr<Something>(new Something));

//     return 0;
// }

int main()
{
    return main_3a();
}