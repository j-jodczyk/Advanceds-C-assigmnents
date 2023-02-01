#include "helper_functions.hpp"

#include <algorithm>
#include <iostream>
#include <random>

namespace helpers {

// helper functions (definitions)

void reset(Vector &vec) {
    vec.clear();
}

void fill_uniform_random(Vector &vec, std::size_t n, value_type lower,
                         value_type upper) {
    // for (size_t i=0; i < n; i++) {
    //     value_type rand_num = lower + rand() / (RAND_MAX / (upper - lower));
    //     vec.push_back(rand_num);
    // }
    std::mt19937 gen(1);
    std::uniform_real_distribution<value_type> dist(lower, upper);
    vec.resize(n);
    std::generate(vec.begin(), vec.end(), [&gen, &dist]() -> auto {return dist(gen);});
}

void print(const Vector &vec) {
    for (auto el : vec) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
    // std::for_each(vec.begin(), vec.end(), [](const auto &item) -> void {std::cout << item << ' ';});
}

Vector copy(const Vector &vec) {
    // Vector copied_vec;
    // for (Vector::const_iterator i = vec.begin(); i != vec.end(); i++) {
    //     copied_vec.push_back(*i);
    // }
    //return copied_vec;
    return vec;
}

void swap(Vector &a, Vector &b) {
    a.swap(b);
}

Vector concat(const Vector &a, const Vector &b) {
    // Vector concat_vec;
    // concat_vec.reserve(a.size()+b.size());
    // concat_vec.insert(concat_vec.end(), a.begin(), a.end());
    // concat_vec.insert(concat_vec.end(), b.begin(), b.end());
    // return concat_vec;
    auto res = a;
    res.insert(res.end(), b.begin(), b.end());
    return res;
}

void sort(Vector &vec, Compare comp) {
    std::sort(vec.begin(), vec.end(), comp);
}

} // namespace helpers
