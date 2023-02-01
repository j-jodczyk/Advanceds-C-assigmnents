#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include <Vector.hpp>

// measures the runtime for initialization using
// a rvalue reference
// a const lvalue reference
// a value
template <bool MOVE> double runtest(std::vector<Vector> initial) {
  using Clock = std::chrono::steady_clock;
  using Duration = std::chrono::duration<double>;

  Vector::value_type *oldDataAddress = initial.back().data();
  Vector::value_type *newDataAddress = nullptr;

  auto start = Clock::now();
  for (auto &it : initial) {
    // if constexpr makes sure the if is evaluated at compiletime
    if constexpr (MOVE) {
      // call constructor with r-value if compile-time MOVE is true
      Vector vec(std::move(it));
      newDataAddress = vec.data();
    } else {
      Vector vec(it);
      newDataAddress = vec.data();
    }
  }
  auto stop = Clock::now();

  std::cout << std::setw(16) << oldDataAddress << " | " << std::setw(16)
            << newDataAddress << " | " << initial.back().data() << "\n\n";

  return Duration(stop - start).count() / initial.size();
}

int main() {
  std::size_t size = 5'000'000; // vector length 5M == ~40MB
  std::size_t n = 5;            // iterations for averaging run time

  // make n vectors that we want to use to initialise n instances of Widget
  std::vector<Vector> initialValues(n, Vector(size, 42));

  std::cout << std::scientific;
  std::cout << std::setprecision(2);

  std::cout << "Copy:\n";
  std::cout << "Old data before  | New data after   | Old Data after\n";
  auto copyTime = runtest<false>(initialValues);
  std::cout << "Move:\n";
  std::cout << "Old data before  | New data after   | Old Data after\n";
  auto moveTime = runtest<true>(initialValues);

  std::cout << "\nRuntimes of constructing vector objects:\n\n";

  std::cout << std::left << std::setw(40)
            << "Copy constructor Vector(const Vector&)" << std::setw(32)
            << "called as Vector(vec)" << std::right << std::setw(10)
            << copyTime << " s" << std::endl;
  std::cout << std::left << std::setw(40) << "Move constructor Vector(Vector&&)"
            << std::setw(32) << "called as Vector(std::move(vec))" << std::right
            << std::setw(10) << moveTime << " s" << std::endl;

  std::cout << "\n" << std::endl;

  return EXIT_SUCCESS;
}