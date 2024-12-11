#pragma once

#include <execution>
#include <utility>
#include "test.hh"

namespace grido {
  
  // container type should be reference
  template <typename Container>
  class for_each_fn {
  public:
    template <typename Func>
    void operator()(Container container, Func && func) const {
      std::cout << "for_each_fn<" << DeclTypeName<Container>()() << ">::operator()\n";
      for(auto iter = container.begin() ; iter != container.end() ; ++iter) {
        func(*iter);
      }
    }
  };

  template <typename Container, typename UnaryFunc>
  void for_each(Container && container, UnaryFunc && func) {
    for_each_fn<Container &&>()(std::forward<Container>(container), std::forward<UnaryFunc>(func));
  }
};
