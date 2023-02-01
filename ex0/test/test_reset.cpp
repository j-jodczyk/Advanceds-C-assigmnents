#include "helper_functions.hpp"
#include <cassert> // assert

int main() {

  using namespace helpers;

  auto vec = Vector();
  vec.push_back(T{1});
  vec.push_back(T{2});
  vec.push_back(T{3});

  reset(vec);

  assert((vec.empty()) && "expected empty");

  return 0;
}