#pragma once

#include <functional> // std::function
#include <vector>     // std::vector

namespace helpers {

// types
using T = double;
using Vector = std::vector<T>;
using value_type = Vector::value_type;
using Compare = std::function<bool(const value_type &a, const value_type &b)>;

// helper functions (declarations)

void reset(Vector &vec);

void fill_uniform_random(Vector &vec, std::size_t n, value_type lower,
                         value_type upper);

void print(const Vector &vec);

Vector copy(const Vector &vec);

void swap(Vector &a, Vector &b);

Vector concat(const Vector &a, const Vector &b);

void sort(Vector &vec, Compare comp);

} // namespace helpers
