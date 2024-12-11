#include "range.hh"
#include "algorithm.hh"
#include <iostream>
// #include "test.hh"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace grido;

static_assert(std::random_access_iterator<integer_as_iterator<int>>, "int as an interator");
static_assert(std::random_access_iterator<integer_as_iterator<std::size_t>>, "std::size_t as an interator");

TEST_CASE("range") {

  basic_integer_range<int> b(5);
  REQUIRE_EQ(b.size(), 5);

}


//   // boost::ut::expect(b.size() == 5);

//   std::cout << "b = " << b << '\n';
//   for (auto const & i: b) {
//     std::cout << DeclTypeName<decltype(i)>()() << ": " << i << "\n";
//   }

//   unit_integer_range u(b);
//   std::cout << "u = " << u << '\n';
//   for (auto const & i: u) {
//     std::cout << DeclTypeName<decltype(i)>()() << ": " << i << "\n";
//   }

//   {
//     integer_range<int> ir(0, 5, -2);
//     std::cout << "ir = " << ir << '\n';
//     for (auto const & i: ir) {
//       std::cout << DeclTypeName<decltype(i)>()() << ": " << i << "\n";
//     }
//   }

//   {
//     integer_range<int> ir(0, -5, -2);
//     std::cout << "ir = " << ir << '\n';
//     for (auto const & i: ir) {
//       std::cout << DeclTypeName<decltype(i)>()() << ": " << i << "\n";
//     }
//   }


// }
