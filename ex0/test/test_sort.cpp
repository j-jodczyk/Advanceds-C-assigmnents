#include "helper_functions.hpp"
#include <cassert> // assert

int main() {

  using namespace helpers;

  auto vec = Vector();
  vec.push_back(value_type{3});
  vec.push_back(value_type{1});
  vec.push_back(value_type{2});

  auto compare_func = [](const auto &a, const auto &b) -> bool { return a < b; };
  sort(vec, compare_func);

  assert((vec[0] == value_type{1}) && "expected 1 at front");
  assert((vec[1] == value_type{2}) && "expected 2 in the middle");
  assert((vec[2] == value_type{3}) && "expected 3 at end");

  return 0;
}