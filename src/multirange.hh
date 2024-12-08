#pragma once

#include <tuple>

namespace grido {



  template <typename ... Axes>
  class multi_range
  {
    template <typename ... T>
    multi_range(T && ... args): _axes(std::forward<T>(args)...) {}


  private:
    std::tuple<Axes...> _axes;
  };

}
