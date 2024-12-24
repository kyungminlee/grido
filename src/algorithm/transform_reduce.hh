#pragma once

#include <utility>

namespace grido {
  template <typename Container>
  class transform_reduce_fn {
  public:
    template <typename T, class BinaryOp, typename UnaryOp>
    constexpr T operator()(Container container, T init, BinaryOp reduce, UnaryOp transform) const {
      T val = init;
      for(auto iter = container.begin() ; iter != container.end() ; ++iter) {
        val = reduce(val, transform(*iter));
      }
      return val;
    }
  };

  template <typename Container, typename T, typename BinaryOp, typename UnaryOp>
  T transform_reduce(Container && container, T init, BinaryOp && reduce, UnaryOp && transform) {
    return transform_reduce_fn<Container &&>()(
        std::forward<Container>(container),
        std::move(init),
        std::forward<BinaryOp>(reduce),
        std::forward<UnaryOp>(transform)
      );
  }
}