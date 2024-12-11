#pragma once
#include <string>
#include <iostream>

template <typename T>
class DeclTypeName {
public:
  std::string operator()() const {
    return typeid(T).name();
  }
};

template <typename T>
class DeclTypeName<T &> {
public:
  std::string operator()() const {
    return DeclTypeName<T>()() + " &";
  }
};

template <typename T>
class DeclTypeName<T &&> {
public:
  std::string operator()() const {
    return DeclTypeName<T>()() + " &&";
  }
};


template <typename T>
class DeclTypeName<T const> {
public:
  std::string operator()() const {
    return DeclTypeName<T>()() + " const";
  }
};


template <typename T>
class VerboseVector {
public:
  VerboseVector(): _data() {
    std::cout << "VerboseVector<" << DeclTypeName<T>()() << ">::VerboseVector()\n";
  }

  ~VerboseVector() {
    std::cout << "VerboseVector<" << DeclTypeName<T>()() << ">::~VerboseVector()\n";
  }

  VerboseVector(std::initializer_list<T> args): _data{args} {
    std::cout << "VerboseVector<" << DeclTypeName<T>()() << ">::VerboseVector(std::initializer_list<T>)\n";
  }

  VerboseVector(VerboseVector const & arg): _data(arg._data) {
    std::cout << "VerboseVector<" << DeclTypeName<T>()() << ">::VerboseVector(VerboseVector const & arg)\n";
  }

  VerboseVector(VerboseVector && arg): _data(std::move(arg._data)) {
    std::cout << "VerboseVector<" << DeclTypeName<T>()() << ">::VerboseVector(VerboseVector && arg)\n";
  }

  VerboseVector & operator=(VerboseVector const & arg) {
    std::cout << "VerboseVector<" << DeclTypeName<T>()() << ">::operator=(VerboseVector const & arg)\n";
    _data = arg._data;
    return *this;
  }

  VerboseVector & operator=(VerboseVector && arg) {
    std::cout << "VerboseVector<" << DeclTypeName<T>()() << ">::operator=(VerboseVector && arg)\n";
    _data = std::move(arg._data);
    return *this;
  }

  void push_back(T const & arg) {
    std::cout << "VerboseVector<" << DeclTypeName<T>()() << ">::push_back(T const &)\n";
    _data.push_back(arg);
  }
  
  void push_back(T && arg) {
    std::cout << "VerboseVector<" << DeclTypeName<T>()() << ">::push_back(T &&)\n";
    _data.push_back(std::move(arg));
  }

  decltype(auto) begin() const { return _data.begin(); }
  decltype(auto) end() const { return _data.end(); }
  decltype(auto) cbegin() const { return _data.cbegin(); }
  decltype(auto) cend() const { return _data.cend(); }
private:
  std::vector<T> _data;
};

