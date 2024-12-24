#pragma once

#include <utility>

namespace grido {
  template <typename Container>
  class reduce_fn {
  public:
    template <typename T, class BinaryOp>
    constexpr T operator()(Container container, T init, BinaryOp op) const {
      T val = init;
      for(auto iter = container.begin() ; iter != container.end() ; ++iter) {
        val = op(val, *iter);
      }
      return val;
    }
  };

  template <typename Container, typename T, typename BinaryOp>
  T reduce(Container && container, T init, BinaryOp && op) {
    return reduce_fn<Container &&>()(
        std::forward<Container>(container),
        std::move(init),
        std::forward<BinaryOp>(op)
      );
  }
}