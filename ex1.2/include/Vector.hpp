#pragma once

#include <cstddef>

class Vector {
public:
  using value_type = double;
  using size_type = std::size_t;

private:
  size_type _size = 0;
  value_type *_data = nullptr;

public:
  Vector();                                    // default ctor
  Vector(size_type n, const value_type &init); // ctor with size and init

  Vector(const Vector &); // copy constructor
  Vector(Vector &&);      // move constructor
  ~Vector();              // destructor

  value_type *data();                // getter for _data
  size_type size();                  // getter for _size
  value_type &operator[](size_type); // acccess via []
};