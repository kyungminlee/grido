#include "range.hh"
#include "algorithm.hh"
#include <iostream>

using namespace grido;

template <typename T>
class DeclTypeName {
public:
  std::string operator()() const {
    return typeid(T).name();
  }
};

template <typename T>
class DeclTypeName<T &> {
public:
  std::string operator()() const {
    return DeclTypeName<T>()() + " &";
  }
};

template <typename T>
class DeclTypeName<T &&> {
public:
  std::string operator()() const {
    return DeclTypeName<T>()() + " &&";
  }
};


template <typename T>
class DeclTypeName<T const> {
public:
  std::string operator()() const {
    return DeclTypeName<T>()() + " const";
  }
};


int main() {
  static_assert(std::random_access_iterator<integer_as_iterator<int>>, "int as an interator");
  static_assert(std::random_access_iterator<integer_as_iterator<std::size_t>>, "std::size_t as an interator");

  basic_integer_range<int> b(5);

  std::cout << "b = " << b << '\n';
  for (auto const & i: b) {
    std::cout << DeclTypeName<decltype(i)>()() << ": " << i << "\n";
  }

  unit_integer_range u(b);
  std::cout << "u = " << u << '\n';
  for (auto const & i: u) {
    std::cout << DeclTypeName<decltype(i)>()() << ": " << i << "\n";
  }

  {
    integer_range<int> ir(0, 5, -2);
    std::cout << "ir = " << ir << '\n';
    for (auto const & i: ir) {
      std::cout << DeclTypeName<decltype(i)>()() << ": " << i << "\n";
    }
  }

  {
    integer_range<int> ir(0, -5, -2);
    std::cout << "ir = " << ir << '\n';
    for (auto const & i: ir) {
      std::cout << DeclTypeName<decltype(i)>()() << ": " << i << "\n";
    }
  }


}
