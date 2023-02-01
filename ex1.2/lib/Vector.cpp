#include "Vector.hpp"

// default constructor
Vector::Vector() {}

// Constructor
Vector::Vector(size_type size, const value_type &value)
    : _size(size), _data(new Vector::value_type[size]) {
  for (std::size_t i = 0; i < _size; ++i) {
    _data[i] = value;
  }
}

// access to raw pointer to the data
Vector::value_type *Vector::data() { return _data; }

// get the number of elements stored in the vector
Vector::size_type Vector::size() { return _size; }

// access an element of the vector (obtaining a reference)
Vector::value_type &Vector::operator[](size_type pos) { return _data[pos]; }