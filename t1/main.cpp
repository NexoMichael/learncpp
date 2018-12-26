#include <iostream>
#include <string>
#include <vector>
#include <stdarg.h>

template <typename T>
std::string to_string(const T &t)
{
  return std::to_string(t);
}

std::string to_string(const std::string t)
{
  return t;
}

template <typename... Args>
std::vector<std::string> func(const Args &... args)
{
  std::vector<std::string> result{std::move(to_string(args))...};
  return result;
}

template <class... T>
auto func2(T... t) -> std::vector<std::string>
{
  std::vector<std::string> s;
  s.reserve(sizeof...(t));
  (s.emplace_back(to_string(t)), ...);

  return s;
}

int main()
{
  auto val = func(1, 2, 4.5, std::string{"aaa"});
  for (auto el : val)
    std::cout << el << "\n";

  auto val2 = func2(1, 2, 4.5, std::string{"aaa"});
  for (auto el : val2)
    std::cout << el << "\n";

  return 0;
}