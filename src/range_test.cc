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
  SUBCASE("basic_integer_range") {
    SUBCASE("int") {
      CHECK_EQ(basic_integer_range<int>(5).size(), 5);
      CHECK_EQ(basic_integer_range<int>(0).size(), 0);
      CHECK_EQ(basic_integer_range<int>(-3).size(), 0);

      basic_integer_range<int> b(5);
      CHECK_EQ(b.size(), 5);
      static_assert(std::is_same_v<decltype(b)::value_type, int>, "value_type");
      for (auto const & i: b) {
        static_assert(std::is_same_v<decltype(i), int const &>, "int type");
      }
      for (auto && i: b) {
        static_assert(std::is_same_v<decltype(i), int &&>, "int type");
      }
    }

    SUBCASE("std::size_t") {
      CHECK_EQ(basic_integer_range<std::size_t>(5).size(), 5);
      CHECK_EQ(basic_integer_range<std::size_t>(0).size(), 0);
      // CHECK_EQ(basic_integer_range<std::size_t>(-3).size(), 0);

      basic_integer_range<std::size_t> b(5);
      CHECK_EQ(b.size(), 5);
      static_assert(std::is_same_v<decltype(b)::value_type, std::size_t>, "value_type");
      for (auto const & i: b) {
        static_assert(std::is_same_v<decltype(i), std::size_t const &>, "int type");
      }
      for (auto && i: b) {
        static_assert(std::is_same_v<decltype(i), std::size_t &&>, "int type");
      }
    }
  }

  SUBCASE("unit_integer_range") {
    CHECK_EQ(unit_integer_range<int>(5).size(), 5);
    CHECK_EQ(unit_integer_range<int>(3, 5).size(), 2);
    basic_integer_range<long> b(5);
    unit_integer_range u(b);
    static_assert(std::is_same_v<decltype(u)::value_type, long>, "value_type");
  }

  SUBCASE("integer_range") {
    CHECK_EQ(integer_range<int>(8).size(), 8);
    CHECK_EQ(integer_range<int>(3, 8).size(), 5);
    CHECK_EQ(integer_range<int>(3, 8, 2).size(), 3);
  }
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
