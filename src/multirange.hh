#pragma once
#include "algorithm.hh"
#include <tuple>

namespace grido {
  class left_layout_type {};
  class right_layout_type {};

  inline constexpr left_layout_type left_layout;
  inline constexpr right_layout_type right_layout;

  template <typename LayoutPolicy, typename ... Axes>
  class multirange {
  public:
    using size_type = std::size_t;
    using index_type = std::ptrdiff_t; // TODO
    using multi_index_type = std::tuple<typename Axes::value_type...>;
    using axes_type = std::tuple<Axes...>;
    using layout_policy = LayoutPolicy;
    static constexpr size_type dimension = sizeof...(Axes);


    template <typename ... Args>
    multirange(Args && ... args): _axes(std::forward<Args>(args)...) {}

    template <std::size_t I>
    std::tuple_element_t<I, axes_type> const & axis() const { return std::get<I>(_axes); }

    size_type size() const {
      return size_impl(std::make_index_sequence<dimension>());
    }

    auto shape() const {
      return std::apply([](auto && ... axes) { return std::make_tuple(axes.size()...); }, _axes);
    }

    // multi_index_type unravel(index_type const & idx) const {
    //   // TODO
    //   return unravel_impl(idx, std::make_index_sequence<dimension>());
    // }

    size_type ravel(multi_index_type const & idx) const {
      return ravel_impl(idx, std::make_index_sequence<dimension>());
    }
  private:

    template <std::size_t ... I>
    size_type size_impl(std::index_sequence<I...>) const {
      return (size_type(1) * ... * std::get<I>(_axes).size());
    }

    template <std::size_t I, std::size_t ... Is>
    size_type ravel_impl(multi_index_type const & idx, std::index_sequence<I, Is...>) const {
      if constexpr (std::is_same_v<layout_policy, left_layout_type>) {
        auto const & axis = std::get<I>(_axes);
        return ravel_impl(idx, std::index_sequence<Is...>()) * axis.size() + axis.ravel(std::get<I>(idx));
      } else if constexpr (std::is_same_v<layout_policy, right_layout_type>) {
        constexpr std::size_t J = dimension - I - 1;
        auto const & axis = std::get<J>(_axes);
        return ravel_impl(idx, std::index_sequence<Is...>()) * axis.size() + axis.ravel(std::get<J>(idx));
      } else {
        return -1;
      }
    }

    size_type ravel_impl(multi_index_type const & idx, std::index_sequence<>) const {
      return size_type(0);
    }

    // template <std::size_t ... Is>
    // multi_index_type unravel_impl(index_type const & idx, std::index_sequence<Is...>) {
    //   if constexpr (std::is_same_v<layout_policy, left_layout_type>) {
    //   } else if constexpr (std::is_same_v<layout_policy, right_layout_type>) {
    //   } else {
    //     static_assert(false, "not supported");
    //   }
    // }

  private:

    axes_type _axes;
  };


  template <typename Layout, typename ... Axes>
  multirange<Layout, Axes...> make_multirange(Layout const & layout, Axes const & ... axes) {
    return multirange<Layout, Axes...>(axes...);
  }


  // fortran layout
  template <typename ... Axes>
  class for_each_fn<multirange<left_layout_type, Axes...> const &> {
  public:
    static constexpr std::size_t D = sizeof...(Axes);
  
    template <typename Func>
    void operator()(multirange<left_layout_type, Axes...> const & range, Func && func) const {
      impl(range, std::forward<Func>(func));
    }
  private:
    template <typename Func, typename ... T>
    void impl(multirange<left_layout_type, Axes...> const & range, Func && func, T && ... args) const {
      static constexpr std::size_t N = sizeof...(args);
      if constexpr (N == D) {
        func(std::forward_as_tuple(std::forward<T>(args)...)); // TODO: to tuple or not to tuple?
      } else {
        static constexpr std::size_t J = D - N - 1;
        for_each(range.template axis<J>(), [&](auto && i) {
          impl(range, func, i, args...);
        });
      }
    }
  };

  // C layout
  template <typename ... Axes>
  class for_each_fn<multirange<right_layout_type, Axes...> const &> {
  public:
    static constexpr std::size_t D = sizeof...(Axes);
  
    template <typename Func>
    void operator()(multirange<right_layout_type, Axes...> const & range, Func && func) const {
      impl(range, std::forward<Func>(func));
    }
  private:
    template <typename Func, typename ... T>
    void impl(multirange<right_layout_type, Axes...> const & range, Func && func, T && ... args) const {
      static constexpr std::size_t N = sizeof...(args);
      if constexpr (N == D) {
        func(std::forward_as_tuple(std::forward<T>(args)...)); // TODO: to tuple or not to tuple?
      } else {
        for_each(range.template axis<N>(), [&](auto && i) {
          impl(range, func, args..., i);
        });
      }
    }
  };

}


