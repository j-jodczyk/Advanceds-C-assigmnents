#include <Distribution.hpp>

#include "testasserts.hpp"

int main() {
  // check if the typedef value_type is set correctly
  static_assert(std::is_same<double, Distribution<double>::value_type>::value,
                "class Distribution does not have the correct public member "
                "typedef 'value_type'");
  static_assert(std::is_same<float, Distribution<float>::value_type>::value,
                "class Distribution does not have the correct public member "
                "typedef 'value_type'");
  static_assert(std::is_same<long, Distribution<long>::value_type>::value,
                "class Distribution does not have the correct public member "
                "typedef 'value_type'");

  // check if constructor for member initialization works
  const double initMean = 42.;
  const double initStddev = 3.14159265;

  // check if correct value_type would be deduced from constructor
  static_assert(
      std::is_same<decltype(Distribution(initMean, initStddev))::value_type,
                   double>::value,
      "Wrong template type deduced from Distribution(double, double)");

  // now actually make class
  Distribution myDist(initMean, initStddev);

  // check public member variable access
  [[maybe_unused]] auto mean = myDist.mean;
  [[maybe_unused]] auto stddev = myDist.stddev;

  TEST_ASSERT(mean == initMean,
              "Mean has the wrong value after it was set explicitly");
  TEST_ASSERT(
      stddev == initStddev,
      "Standard deviation has the wrong value after it was set explicitly");

  return 0;
}