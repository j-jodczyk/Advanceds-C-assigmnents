#include "Vector.hpp"
#include <algorithm>

// copy constructor
Vector::Vector(const Vector &other)
    : _size(other._size), _data(new value_type[_size]) {
        std::copy(other._data, other._data + _size, _data);
    }

// move constructor
Vector::Vector(Vector &&other)
    : _size(0), _data(nullptr) {
        std::swap(other._size, _size);
        std::swap(other._data, _data);
    }

// destructor
Vector::~Vector() {
    delete[] _data;
}