#include "helper_functions.hpp"
#include <cassert> // assert
#include <cmath>   // abs
#include <numeric> // accumulate

int main() {

  using namespace helpers;

  auto vec = Vector();
  fill_uniform_random(vec, 1'000, -1.0, 1.0);

  assert((vec.size() == 1'000) && "expected 1K size");

  auto avg =
      std::accumulate(vec.begin(), vec.end(), value_type{0}) / vec.size();

  assert((std::abs(avg) < 1e-1) && "expected avg around zero");

  return 0;
}