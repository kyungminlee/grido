#pragma once

#include <tuple>
#include <iostream>

namespace grido {

  template <typename T>
  class StreamWriter {
  public:
    template <typename Ch, typename Tr>
    void operator()(std::basic_ostream<Ch, Tr> & os, T const & item) const {
      os << item;
    }
  };

  template <typename Ch, typename Tr, typename ... T>
  void write_to_stream(std::basic_ostream<Ch, Tr> & os, T const & ... args) {
    (StreamWriter<T>()(os, args), ...);
  }
  

  template <typename ... T>
  class StreamWriter<std::tuple<T...>> {
  public:
    template <typename Ch, typename Tr>
    void operator()(std::basic_ostream<Ch, Tr> & os, std::tuple<T...> const & item) const {
      os << '(';
      write(os, item, std::make_index_sequence<sizeof...(T)>());
      os << ')';
    }

    template <typename Ch, typename Tr, std::size_t I, std::size_t J, std::size_t ... K>
    void write(std::basic_ostream<Ch, Tr> & os, std::tuple<T...> const & item, std::index_sequence<I, J, K...>) const {
      write_to_stream(os, std::get<I>(item), ", ");
      write(os, item, std::index_sequence<J, K...>());
    }

    template <typename Ch, typename Tr, std::size_t I>
    void write(std::basic_ostream<Ch, Tr> & os, std::tuple<T...> const & item, std::index_sequence<I>) const {
      write_to_stream(os, std::get<I>(item));
    }

    template <typename Ch, typename Tr>
    void write(std::basic_ostream<Ch, Tr> & os, std::tuple<T...> const & item, std::index_sequence<>) const {
    }

  };


};