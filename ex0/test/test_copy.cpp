#include "helper_functions.hpp"
#include <cassert> // assert

int main() {

  using namespace helpers;

  auto vec = Vector();
  vec.push_back(T{1});
  vec.push_back(T{2});
  vec.push_back(T{3});

  auto clone = copy(vec);

  assert((clone[0] == vec[0]) && "expected equal first value");
  assert((clone[1] == vec[1]) && "expected equal second value");
  assert((clone[2] == vec[2]) && "expected equal third value");
  assert((clone.size() == vec.size()) && "expected equal size");

  return 0;
}