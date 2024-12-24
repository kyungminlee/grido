#pragma once

#include "algorithm/algorithm.hh"
#include <cstddef>
#include <type_traits>
#include <iterator>
#include <algorithm>

namespace grido {
  template <typename T>
  class integer_as_iterator {
  public:
    using value_type = T;
    using difference_type = std::make_signed_t<value_type>;
    using reference = value_type;
    using const_reference = value_type;
    using pointer = void;
    using iterator_category = std::random_access_iterator_tag;

    static_assert(std::is_integral_v<value_type>, "value tyoe must be integral");

    integer_as_iterator() noexcept : _value(0) {}
    integer_as_iterator(integer_as_iterator const &) noexcept = default;
    integer_as_iterator(integer_as_iterator &&) noexcept = default;
    integer_as_iterator & operator=(integer_as_iterator const &) noexcept = default;
    integer_as_iterator & operator=(integer_as_iterator &&) noexcept = default;

    integer_as_iterator(value_type const & value): _value(value) {}
    integer_as_iterator(value_type && value): _value(std::move(value)) {}

    value_type value() const { return _value; }
    operator value_type() const { return _value; }

    value_type operator*() const { return _value; }

#if __cplusplus >= 202002L
    std::strong_ordering operator<=>(integer_as_iterator const & rhs) const { return _value <=> rhs._value; }
#else
    bool operator==(integer_as_iterator const & rhs) const { return _value == rhs._value; }
    bool operator!=(integer_as_iterator const & rhs) const { return _value != rhs._value; }
    bool operator< (integer_as_iterator const & rhs) const { return _value <  rhs._value; }
    bool operator> (integer_as_iterator const & rhs) const { return _value >  rhs._value; }
    bool operator<=(integer_as_iterator const & rhs) const { return _value <= rhs._value; }
    bool operator>=(integer_as_iterator const & rhs) const { return _value >= rhs._value; }
#endif

    integer_as_iterator & operator++() { ++_value; return *this; }
    integer_as_iterator & operator--() { --_value; return *this; }
    integer_as_iterator & operator+=(difference_type n) { _value += n; return *this; }
    integer_as_iterator & operator-=(difference_type n) { _value -= n; return *this; }

    integer_as_iterator operator++(int) { integer_as_iterator out(*this); ++(*this); return out; }
    integer_as_iterator operator--(int) { integer_as_iterator out(*this); --(*this); return out; }

    integer_as_iterator operator+(difference_type n) const { return integer_as_iterator(_value + n); }
    integer_as_iterator operator-(difference_type n) const { return integer_as_iterator(_value - n); }
    friend integer_as_iterator operator+(difference_type n, integer_as_iterator const & rhs) {
      return integer_as_iterator(n + rhs._value);
    }

    value_type operator[](difference_type const & n) const { return _value + n; }

    difference_type operator-(integer_as_iterator const & rhs) const {
      return static_cast<difference_type>(_value) - static_cast<difference_type>(rhs._value);
    }

  private:
    value_type _value;
  };


  template <typename T>
  class integer_multiple_as_iterator {
  public:
    using value_type = T;
    using difference_type = std::make_signed_t<value_type>;
    using reference = value_type;
    using const_reference = value_type;
    using pointer = void;
    using iterator_category = std::random_access_iterator_tag;

    static_assert(std::is_integral_v<value_type>, "value tyoe must be integral");

    integer_multiple_as_iterator() noexcept : _value(0), _step(1) {}
    integer_multiple_as_iterator(integer_multiple_as_iterator const &) noexcept = default;
    integer_multiple_as_iterator(integer_multiple_as_iterator &&) noexcept = default;
    integer_multiple_as_iterator & operator=(integer_multiple_as_iterator const &) noexcept = default;
    integer_multiple_as_iterator & operator=(integer_multiple_as_iterator &&) noexcept = default;

    integer_multiple_as_iterator(value_type const & value, difference_type const & step): _value(value), _step(step) {}

    value_type value() const { return _value; }
    operator value_type() const { return _value; }

    value_type operator*() const { return _value; }

#if __cplusplus >= 202002L
    std::strong_ordering operator<=>(integer_multiple_as_iterator const & rhs) const { return _value <=> rhs._value; }
#else
    bool operator==(integer_multiple_as_iterator const & rhs) const { return _value == rhs._value; }
    bool operator!=(integer_multiple_as_iterator const & rhs) const { return _value != rhs._value; }
    bool operator< (integer_multiple_as_iterator const & rhs) const { return _value <  rhs._value; }
    bool operator> (integer_multiple_as_iterator const & rhs) const { return _value >  rhs._value; }
    bool operator<=(integer_multiple_as_iterator const & rhs) const { return _value <= rhs._value; }
    bool operator>=(integer_multiple_as_iterator const & rhs) const { return _value >= rhs._value; }
#endif

    integer_multiple_as_iterator & operator++() { _value += _step; return *this; }
    integer_multiple_as_iterator & operator--() { _value -= _step; return *this; }
    integer_multiple_as_iterator & operator+=(difference_type n) { _value += _step * n; return *this; }
    integer_multiple_as_iterator & operator-=(difference_type n) { _value -= _step * n; return *this; }

    integer_multiple_as_iterator operator++(int) { integer_multiple_as_iterator out(*this); ++(*this); return out; }
    integer_multiple_as_iterator operator--(int) { integer_multiple_as_iterator out(*this); --(*this); return out; }

    integer_multiple_as_iterator operator+(difference_type n) const { return integer_multiple_as_iterator(_value + _step * n); }
    integer_multiple_as_iterator operator-(difference_type n) const { return integer_multiple_as_iterator(_value - _step * n); }
    friend integer_multiple_as_iterator operator+(difference_type n, integer_multiple_as_iterator const & rhs) {
      return integer_multiple_as_iterator(rhs._step * n + rhs._value);
    }

    value_type operator[](difference_type const & n) const { return _value + _step * n; }

    difference_type operator-(integer_multiple_as_iterator const & rhs) const {
      return (static_cast<difference_type>(_value) - static_cast<difference_type>(rhs._value)) / _step;
    }

  private:
    value_type _value;
    difference_type _step;
  };

  template <typename I> class basic_integer_range;
  template <typename I> class unit_integer_range;
  template <typename I, typename S> class integer_range;

  template <typename I>
  class basic_integer_range {
  public:
    using value_type = I;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using const_iterator = integer_as_iterator<value_type>;
    using iterator = const_iterator;

    constexpr basic_integer_range() noexcept : _end(0) {}
    constexpr basic_integer_range(basic_integer_range const &) noexcept = default;
    constexpr basic_integer_range(basic_integer_range &&) noexcept = default;
    constexpr basic_integer_range & operator=(basic_integer_range const &) noexcept = default;
    constexpr basic_integer_range & operator=(basic_integer_range &&) noexcept = default;

    constexpr explicit basic_integer_range(value_type const & end) noexcept : _end(std::max(value_type(0), end)) {}

    constexpr size_type size() const { return _end; }
    constexpr const_iterator cbegin() const { return const_iterator(0); }
    constexpr const_iterator cend() const { return const_iterator(_end); }
    constexpr const_iterator begin() const { return const_iterator(0); }
    constexpr const_iterator end() const { return const_iterator(_end); }
    constexpr value_type operator[](difference_type n) const { return n; }
    constexpr size_type ravel(value_type const & v) const { return v; }

    template <typename V>
    explicit operator basic_integer_range<V>() const { return basic_integer_range<V>(V(_end)); }

    template <typename Ch, typename Tr>
    friend std::basic_ostream<Ch, Tr> & operator<<(std::basic_ostream<Ch, Tr> & os, basic_integer_range const & r) {
      return os << ':' << r._end;
    }

    friend class for_each_fn<basic_integer_range const &>;

  private:
    value_type _end;
  }; // class basic_integer_range


  template <typename I>
  class for_each_fn<basic_integer_range<I> const &> {
  public:
    template <typename Func>
    void operator()(basic_integer_range<I> const & container, Func && func) const {
      for(I i = 0 ; i != container._end ; ++i) {
        func(i);
      }
    }
  };


  template <typename I>
  class unit_integer_range {
  public:
    using value_type = I;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using const_iterator = integer_as_iterator<value_type>;
    using iterator = const_iterator;

    constexpr unit_integer_range() noexcept : _begin(0), _end(0) {}
    constexpr unit_integer_range(unit_integer_range const &) noexcept = default;
    constexpr unit_integer_range(unit_integer_range &&) noexcept = default;
    constexpr unit_integer_range & operator=(unit_integer_range const &) noexcept = default;
    constexpr unit_integer_range & operator=(unit_integer_range &&) noexcept = default;

    constexpr explicit unit_integer_range(value_type const & end) noexcept
        : _begin(0), _end(std::max(value_type(0), end)) {}
    constexpr explicit unit_integer_range(value_type const & begin, value_type const & end) noexcept
        : _begin(begin), _end(std::max(begin, end)) {}

    constexpr unit_integer_range(basic_integer_range<value_type> const & arg) : _begin(0), _end(*arg.end()) {}

    constexpr size_type size() const { return _end - _begin; }
    constexpr const_iterator cbegin() const { return const_iterator(_begin); }
    constexpr const_iterator cend() const { return const_iterator(_end); }
    constexpr const_iterator begin() const { return const_iterator(_begin); }
    constexpr const_iterator end() const { return const_iterator(_end); }
    constexpr value_type operator[](difference_type n) const { return _begin + n; }

    constexpr size_type ravel(value_type const & v) const { return v - _begin; }


    template <typename V>
    explicit operator unit_integer_range<V>() const { return unit_integer_range<V>(V(_end)); }

    template <typename Ch, typename Tr>
    friend std::basic_ostream<Ch, Tr> & operator<<(std::basic_ostream<Ch, Tr> & os, unit_integer_range const & r) {
      return os << r._begin << ':' << r._end;
    }

    friend class for_each_fn<unit_integer_range const &>;

  private:
    value_type _begin;
    value_type _end;
  }; // class unit_integer_range


  template <typename I>
  class for_each_fn<unit_integer_range<I> const &> {
  public:
    template <typename Func>
    void operator()(unit_integer_range<I> const & container, Func && func) const {
      for(I i = container._begin ; i != container._end ; ++i) {
        func(i);
      }
    }
  };


  template <typename T, typename D>
  constexpr T proper_end(T const & begin, T const & end, D const & step) { 
    using S = std::make_signed_t<T>;
    S b = begin;
    S e = end;
    S s = step;
    constexpr S z = 0;
    if (step > 0) {
      S n = std::max(z, (e - b + s - 1) / s);
      return begin + n * step;
    } else if (step < 0) {
      S n = std::min(z, (b - e - s - 1) / s);
      return begin - n * step;
    } else {
      return begin;
    }
  }


  template <typename I, typename S=std::make_signed_t<I>>
  class integer_range {
  public:
    using value_type = I;
    using step_type = S;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using const_iterator = integer_multiple_as_iterator<value_type>;
    using iterator = const_iterator;

    constexpr integer_range() noexcept : _begin(0), _end(0), _step(1) {}
    constexpr integer_range(integer_range const &) noexcept = default;
    constexpr integer_range(integer_range &&) noexcept = default;
    constexpr integer_range & operator=(integer_range const &) noexcept = default;
    constexpr integer_range & operator=(integer_range &&) noexcept = default;

    constexpr explicit integer_range(value_type const & end) noexcept
        : _begin(0), _end(std::max(value_type(0), end)), _step(1) {}
    constexpr explicit integer_range(value_type const & begin, value_type const & end) noexcept
        : _begin(begin), _end(std::max(begin, end)), _step(1) {}

    constexpr explicit integer_range(value_type const & begin, value_type const & end, step_type const & step) noexcept
        : _begin(begin), _end(proper_end(begin, end, step)), _step(step) {}

    constexpr explicit integer_range(basic_integer_range<value_type> const & arg) noexcept
        : _begin(0), _end(*arg.end()), _step(1) {}
    constexpr explicit integer_range(unit_integer_range<value_type> const & arg) noexcept
        : _begin(*arg.begin()), _end(*arg.end()), _step(1) {}

    constexpr size_type size() const { return (_end - _begin) / _step; }
    constexpr const_iterator cbegin() const { return const_iterator(_begin, _step); }
    constexpr const_iterator cend() const { return const_iterator(_end, _step); }
    constexpr const_iterator begin() const { return const_iterator(_begin, _step); }
    constexpr const_iterator end() const { return const_iterator(_end, _step); }
    constexpr value_type operator[](difference_type n) const { return _begin + n * _step; }
    constexpr size_type ravel(value_type const & v) const { return (v - _begin) / _step; }

    template <typename V>
    explicit operator integer_range<V>() const { return integer_range<V>(V(_end)); }

    template <typename Ch, typename Tr>
    friend std::basic_ostream<Ch, Tr> & operator<<(std::basic_ostream<Ch, Tr> & os, integer_range const & r) {
      return os << r._begin << ':' << r._end << ':' << r._step;
    }

    step_type const & step() const { return _step; }

    friend class for_each_fn<integer_range const &>;

  private:
    value_type _begin;
    value_type _end;
    step_type _step;
  }; // class integer_range


  // container type should be reference
  template <typename I, typename S>
  class for_each_fn<integer_range<I, S> const &> {
  public:
    template <typename Func>
    void operator()(integer_range<I, S> const & container, Func && func) const {
      for(I i = container._begin ; i != container._end ; i += container._step) {
        func(i);
      }
    }
  };


} // namespac grido
