#include <list>

#include <Distribution.hpp>
#include <SpaceVector.hpp>

#include "testasserts.hpp"

template<class T>
using CONTAINER = std::list<T>;

template <class T> Distribution<T> makeDistribution() {
  // populate vector with simple values for small Distribution
  CONTAINER<T> ctnr{0, 250, 750, 1000};

  Distribution myDist(ctnr);
  return myDist;
}

template <class T>
Distribution<SpaceVector<T, 3>> makeSpaceVectorDistribution() {
  CONTAINER<SpaceVector<T, 3>> vec{
      {0, 0, 0}, {250, 500, 750}, {750, 1500, 2250}, {1000, 2000, 3000}};

  Distribution myDist(vec);
  return myDist;
}

int main() {
  auto doubleDist = makeDistribution<double>();
  TEST_ASSERT_IN_RANGE(doubleDist.mean, 499.99, 500.01, "Double mean: ");
  TEST_ASSERT_IN_RANGE(doubleDist.stddev, 395.28, 395.29, "Double stddev: ");

  auto floatDist = makeDistribution<float>();
  TEST_ASSERT_IN_RANGE(floatDist.mean, 499.99, 500.01, "Float mean: ");
  TEST_ASSERT_IN_RANGE(floatDist.stddev, 395.28, 395.29, "Float stddev: ");

  auto longDist = makeDistribution<long>();
  TEST_ASSERT_IN_RANGE(longDist.mean, 500, 500, "Long mean: ");
  TEST_ASSERT_IN_RANGE(longDist.stddev, 395, 395, "Long stddev: ");

  auto spaceDist = makeSpaceVectorDistribution<double>();
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