#include <vector>

#include <Distribution.hpp>
#include <SpaceVector.hpp>

#include "testasserts.hpp"

template <class T>
Distribution<SpaceVector<T, 3>> makeSpaceVectorDistribution() {
  std::vector<SpaceVector<T, 3>> vec{
      {0, 0, 0}, {250, 500, 750}, {750, 1500, 2250}, {1000, 2000, 3000}};
  Distribution myDist(vec);
  return myDist;
}

int main() {
  // test constructor which calculates mean and stddev
  {
    // make vector with 10 elements with value 1.
    std::vector<SpaceVector<double, 3>> myVec(10, {1, 2, 3});

    // check if correct value_type would be deduced
    static_assert(std::is_same<decltype(Distribution(myVec))::value_type,
                               SpaceVector<double, 3>>::value,
                  "Wrong type deduced from std::vector<SpaceVector<double, 3>>");

    // make distribution from vector
    auto spaceDist = Distribution(myVec);

    // check if values are correct
    TEST_ASSERT_IN_RANGE(spaceDist.mean[0], 0.99, 1.01,
                         "Wrong mean[0] value for Distribution<double>: ");
    TEST_ASSERT_IN_RANGE(spaceDist.mean[1], 1.99, 2.01,
                         "Wrong mean[1] value for Distribution<double>: ");
    TEST_ASSERT_IN_RANGE(spaceDist.mean[2], 2.99, 3.01,
                         "Wrong mean[2] value for Distribution<double>: ");
    TEST_ASSERT_IN_RANGE(spaceDist.stddev[0], -0.01, 0.01,
                         "Wrong stddev[0] value for Distribution<double>: ");
    TEST_ASSERT_IN_RANGE(spaceDist.stddev[1], -0.01, 0.01,
                         "Wrong stddev[1] value for Distribution<double>: ");
    TEST_ASSERT_IN_RANGE(spaceDist.stddev[2], -0.01, 0.01,
                         "Wrong stddev[2] value for Distribution<double>: ");
  }

  [[maybe_unused]] auto spaceDist = makeSpaceVectorDistribution<double>();

  TEST_ASSERT_IN_RANGE(spaceDist.mean[0], 499.99, 500.01,
                       "SpaceVector.mean[0]: ");
  TEST_ASSERT_IN_RANGE(spaceDist.mean[1], 999.99, 1000.01,
                       "SpaceVector.mean[1]: ");
  TEST_ASSERT_IN_RANGE(spaceDist.mean[2], 1499.99, 1500.01,
                       "SpaceVector.mean[2]: ");

  TEST_ASSERT_IN_RANGE(spaceDist.stddev[0], 395.28, 395.29,
                       "SpaceVector.stddev[0]: ");
  TEST_ASSERT_IN_RANGE(spaceDist.stddev[1], 790.56, 790.57,
                       "SpaceVector.stddev[1]: ");
  TEST_ASSERT_IN_RANGE(spaceDist.stddev[2], 1185.85, 1185.86,
                       "SpaceVector.stddev[2]: ");

  return 0;
}