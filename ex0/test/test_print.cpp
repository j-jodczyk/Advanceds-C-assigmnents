#include "helper_functions.hpp"

int main() {

  using namespace helpers;

  auto vec = Vector();
  vec.push_back(T{1.1332});
  vec.push_back(T{9.99});
  vec.push_back(T{3.1});

  print(vec); // output checked by ctest

  return 1; // this output is neglected
}