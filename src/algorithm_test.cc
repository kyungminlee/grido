#include "algorithm.hh"
#include "range.hh"
#include "test.hh"
#include <vector>
#include <iostream>

using namespace grido;



int main() {
  VerboseVector<double> v{0.1, 0.2, 0.3};

  grido::for_each(v, [](double const & v) {
    std::cout << "item: " << v << std::endl;
  });
  auto const & v2 = v;
  grido::for_each(v2, [](double const & v) {
    std::cout << "item: " << v << std::endl;
  });
  
  grido::for_each(std::move(v), [](double const & v) {
    std::cout << "item: " << v << std::endl;
  });

  grido::integer_range<std::size_t, int> range(3, 8, 2);
  grido::for_each(range, [](auto && i) {
    std::cout << "range item: " << i << std::endl;
  });
}