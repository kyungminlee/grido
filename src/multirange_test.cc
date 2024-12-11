#include "range.hh"
#include "multirange.hh"
#include "utility.hh"

int main() {
  using namespace grido;

  basic_integer_range bir(5);
  unit_integer_range uir(2, 9);
  integer_range ir(3, 8, 2);

  std::cout << ir.size() << std::endl;
  std::cout << uir.size() << std::endl;

  {
    auto mr = make_multirange(left_layout, bir, uir, ir);
    std::cout << mr.size() << std::endl;
    write_to_stream(std::cout, mr.shape(), '\n');

    auto const & mmr = mr;
    for_each(mmr, [&](auto && indices) {
      write_to_stream(std::cout, "tuple: ", indices, " => ", mmr.ravel(indices), '\n');
    });
  }
  
  {
  auto mr = make_multirange(right_layout, bir, uir, ir);

  auto const & mmr = mr;
  for_each(mmr, [&](auto && indices) {
    write_to_stream(std::cout, "tuple: ", indices, " => ", mmr.ravel(indices), '\n');
  });
  }
}