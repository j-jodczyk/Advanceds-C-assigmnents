#include <algorithm>
#include <cmath>
#include <iterator>
#include <vector>

int main() {
  // try changing this container type and see if everything still works
  using Container = std::vector<double>;
  Container vec(10, 10);
  Container::value_type value = 5;

  // ---------------------------------- Iterator Basics

  { // obtaining iterators using <iterator> header
    [[maybe_unused]] auto iter_begin =
        std::begin(vec); // [[maybe_unused]] avoids compiler warning
    [[maybe_unused]] auto iter_end = std::end(vec);
    [[maybe_unused]] auto const_iter_begin = std::cbegin(vec);
    [[maybe_unused]] auto const_iter_end = std::cend(vec);
  }

  { // obtaining iterators from member function
    [[maybe_unused]] auto iter_begin = vec.begin();
    [[maybe_unused]] auto iter_end = vec.end();
    [[maybe_unused]] auto const_iter_begin = vec.cbegin();
    [[maybe_unused]] auto const_iter_end = vec.cend();
  }

  { // the end element is "one past the last element"
    auto iter_end = vec.end();
    // value = *iter_end; // access out-of-bounds (LEADS TO SEGFAULT IF USED)
    --iter_end; // move iterator back once to point to last element
    if (iter_end != vec.end()) { // check if we are out of bounds
      value = *iter_end;         // guarded access
    }
  }

  // ----------------------------------  Iterator Usage to fill data structure

  // classic for-loop with index
  for (std::size_t i = 0; i < vec.size(); ++i) {
    vec[i] = value; // access value using operator[]
  }

  // classic for-loop with iterators
  // std::end(vec) must point to past the end, so the last element is still
  // included in the for loop
  for (auto iter = std::begin(vec); iter != std::end(vec); ++iter) {
    *iter = value; // access value using dereferenced iterator
  }

  // range based for loop (requires and uses iterators under the hood)
  for (auto &item : vec) { // take reference `auto &` to each element
    item = value; // direct access to value through `auto &item`
  }
  { // this is how it looks "under the hood"
    auto begin = vec.begin();
    auto end = vec.end();
    for (; begin != end; ++begin) {
      auto &item = *begin; // `auto &` as in the range-based for loop
      item = value;
    }
  }

  // using an STL algorithm to do the filling for us
  std::fill(vec.begin(), vec.end(), value);

  // ---------------------------------- Iterator usage with standard library

  // usage example for an algorithm in the <algorithm> header
  // apply a transform (sin) to vector and store in a new vector
  Container newvec(10);
  std::transform(
      // take elements from the vec.begin() to vec.end()
      // and write starting at newvec.begin()
      vec.begin(), vec.end(), newvec.begin(),
      [](const Container::value_type &element) { return std::sin(element); });

}