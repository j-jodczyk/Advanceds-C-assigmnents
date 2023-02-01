#include <algorithms.hpp>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

using value_type = int;
using Vector = std::vector<value_type>;

const std::size_t size = 10;
const value_type start = 0;
const value_type scale = 2;

bool isBelowMean(const value_type &element) {
  return element < value_type{(start + size / 2) * scale};
}

int main() {
  Vector vec(size);

  // populate with sequence
  populate_with_sequence(vec, start);
  std::cout << "populate_with_sequence: " << std::endl;
  print(std::cout, vec);

  // multiply with value
  multiply_with_value(vec, scale);
  std::cout << "\n\nmultiply_with_value: " << scale << std::endl;
  print(std::cout, vec);

  // reverse order
  reverse_order(vec);
  std::cout << "\n\nreverse_order: " << std::endl;
  print(std::cout, vec);

  // check how many elements are below the mean value
  auto count = count_fulfills_cond(vec, &isBelowMean);
  const value_type expected_count = size / 2;
  std::cout << "\n\ncount_fulfills_cond: " << count
            << ", expected: " << expected_count << std::endl;

  // make copy to check if they are equal
  {
    Vector vec_copy = vec;
    auto iter = vec_copy.begin();
    std::advance(iter, vec_copy.size() / 2);
    *iter += value_type{1};
    std::cout << "\nvec_copy: " << std::endl;
    print(std::cout, vec_copy);

    auto equal = first_n_equal(vec, vec_copy, 5);
    std::cout << "\nfirst 5 equal: " << equal
              << ", expected: " << true << std::endl;
    
    equal = first_n_equal(vec, vec_copy, 7);
    std::cout << "\nfirst 7 equal: " << equal
              << ", expected: " << false << std::endl;
  }
  
  // sum of elements
  auto sum = sum_of_elements(vec);
  const value_type expected_sum =
      (((size * size + size) / 2) + size * (start - 1)) * scale;
  std::cout << "\nsum: " << sum << ", expected: " << expected_sum
            << std::endl;

  // multiply with value
  multiply_with_value(vec, value_type{-1});
  std::cout << "\nmultiply_with_value: " << std::endl;
  print(std::cout, vec);

  // absolute sum of all elements
  auto abssum = abssum_of_elements(vec);
  const value_type expected_abssum =
      (((size * size + size) / 2) + size * (start - 1)) * scale;
  std::cout << "\n\nabssum: " << abssum
            << ", expected: " << expected_abssum << std::endl;
}
