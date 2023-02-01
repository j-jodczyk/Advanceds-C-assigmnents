#include "helper_functions.hpp"
#include <cassert> // assert

int main() {

  using namespace helpers;

  auto a = Vector(1, value_type{1});
  auto b = Vector(1, value_type{2});

  auto c = concat(a, b);

  assert((c[0] == a[0]) && "expected a at front");
  assert((c[1] == b[0]) && "expected b after");

  return 0;
}