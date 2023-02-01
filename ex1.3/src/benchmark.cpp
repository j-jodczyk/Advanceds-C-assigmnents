#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include <List.hpp>

// measures the runtime for initialization using
// a rvalue reference
// a const lvalue reference
// a value
template <bool MOVE, bool ASSIGN> double runtest(std::vector<List> initial) {
  using Clock = std::chrono::steady_clock;
  using Duration = std::chrono::duration<double>;

  const List::Node *oldDataAddress = initial.back().data();
  const List::Node *newDataAddress = nullptr;

  const auto numberOfElements = initial.back().size();
  List list(numberOfElements, 1.);
  Duration duration = {};

  for (auto &it : initial) {
    // if constexpr makes sure the if is evaluated at compile time
    if constexpr (MOVE) {
      if constexpr (ASSIGN) {
        auto start = Clock::now();
        list = std::move(it);
        auto stop = Clock::now();
        newDataAddress = list.data();
        duration += Duration(stop - start);
      } else {
        auto start = Clock::now();
        List list(std::move(it));
        auto stop = Clock::now();
        newDataAddress = list.data();
        duration += Duration(stop - start);
      }
    } else {
      if constexpr (ASSIGN) {
        auto start = Clock::now();
        list = it;
        auto stop = Clock::now();
        newDataAddress = list.data();
        duration += Duration(stop - start);
      } else {
        auto start = Clock::now();
        List list(it);
        auto stop = Clock::now();
        newDataAddress = list.data();
        duration += Duration(stop - start);
      }
    }
  }

  std::cout << std::setw(16) << oldDataAddress << " | " << std::setw(16)
            << newDataAddress << " | " << initial.back().data() << "\n\n";

  return duration.count() / initial.size();
}

int main() {
  std::size_t size = 100'000; // list length 0.1M == ~1.6 MB
  std::size_t n = 5;          // iterations for averaging run time

  // make n Lists filled with 1k elements each
  std::vector<List> initialValues(n, List(size, 42.));

  std::cout << std::scientific;
  std::cout << std::setprecision(2);

  std::cout << "Copy:\n";
  std::cout << "Old data before  | New data after   | Old Data after\n";
  auto copyTime = runtest<false, false>(initialValues);
  std::cout << "Move:\n";
  std::cout << "Old data before  | New data after   | Old Data after\n";
  auto moveTime = runtest<true, false>(initialValues);

  std::cout << "Copy Assign:\n";
  std::cout << "Old data before  | New data after   | Old Data after\n";
  auto cassTime = runtest<false, true>(initialValues);
  std::cout << "Move Assign:\n";
  std::cout << "Old data before  | New data after   | Old Data after\n";
  auto massTime = runtest<true, true>(initialValues);

  std::cout << "\nRuntimes of constructing list objects:\n\n";

  std::cout << std::left << std::setw(40)
            << "Copy constructor List(const List&)" << std::setw(34)
            << "called as List(list)" << std::right << std::setw(10) << copyTime
            << " s" << std::endl;
  std::cout << std::left << std::setw(40) << "Move constructor List(List&&)"
            << std::setw(34) << "called as List(std::move(list))" << std::right
            << std::setw(10) << moveTime << " s" << std::endl;

  std::cout << std::left << std::setw(40)
            << "Copy assignment operator=(const List&)" << std::setw(34)
            << "called as listB = listA" << std::right << std::setw(10)
            << cassTime << " s" << std::endl;
  std::cout << std::left << std::setw(40) << "Move assignment operator=(List&&)"
            << std::setw(34) << "called as listB = std::move(listA)"
            << std::right << std::setw(10) << massTime << " s" << std::endl;

  std::cout << "\n" << std::endl;

  return EXIT_SUCCESS;
}