#include <Distribution.hpp>
#include <SpaceVector.hpp>

#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <vector>

template <class C>
Distribution<double> populate_with_Distribution(C &container) {
  using T = typename C::value_type;
  const std::size_t size = 100'000;

  // setup varying normal Distribution
  std::random_device rd;
  std::mt19937 gen(rd()); // PRNG
  std::uniform_real_distribution<> uniDist(0.0, 1.0);

  // Explicitly initialise Distribution with type double
  // because std::normal_distribution can only handle doubles
  Distribution<double> initial(uniDist(gen) * 100.0, uniDist(gen) * 10.0);

  // populate container by drawing from normal Distribution
  std::normal_distribution normalDist(initial.mean, initial.stddev);
  for (unsigned i = 0; i < size; ++i) {
    T value(normalDist(gen));
    container.insert(container.end(), value);
  }

  // return Distribution
  return initial;
}

template <class D1, class D2> void print_difference(D1 &initial, D2 &final) {
  std::cout << "    mean = " << std::setprecision(3) << std::fixed
            << (final.mean - initial.mean)
            << "; stddev = " << (final.stddev - initial.stddev) << std::endl;
}

template <class U> void test_types() {
  using T = typename U::value_type;
  if constexpr (std::is_same<U, std::vector<T>>::value) {
    std::cout << "  Vector: " << std::endl;
  } else if (std::is_same<U, std::list<T>>::value) {
    std::cout << "  List: " << std::endl;
  } else if (std::is_same<U, std::deque<T>>::value) {
    std::cout << "  Deque: " << std::endl;
  }
  U ctnr;
  Distribution init_distr = populate_with_Distribution(ctnr);
  Distribution final_distr(ctnr);
  print_difference(init_distr, final_distr);
}

template <class T> void test_containers() {
  test_types<std::vector<T>>();
  test_types<std::list<T>>();
  test_types<std::deque<T>>();
}

int main() {
  std::cout << "Differences between original Distribution and randomly "
               "generated Distribution:"
            << std::endl;
  std::cout << "double:" << std::endl;
  test_containers<double>();

  std::cout << "long:" << std::endl;
  test_containers<long>();

  std::cout << "float:" << std::endl;
  test_containers<float>();

  std::cout << "SpaceVector<double>:" << std::endl;
  test_containers<SpaceVector<double,3>>();

  return 0;
}
