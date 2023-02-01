#include "helper_functions.hpp"
#include <cassert> // assert

int main() {

  using namespace helpers;

  auto a = Vector(1, value_type{1});
  auto b = Vector(1, value_type{2});
  const auto a_data = a.data();
  const auto b_data = b.data();

  swap(a, b);

  assert((a[0] == value_type{2}) && "expected two");
  assert((b[0] == value_type{1}) && "expected one");

  assert((a_data == b.data()) && "expected swap");
  assert((b_data == a.data()) && "expected swap");

  return 0;
}