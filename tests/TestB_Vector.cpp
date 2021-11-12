#include <vector>

#include <Distribution.hpp>
#include <SpaceVector.hpp>

#include "testasserts.hpp"

template <class T> Distribution<T> makeDistribution() {
  // populate vector with simple values for small Distribution
  std::vector<T> ctnr{0, 250, 750, 1000};

  Distribution myDist(ctnr);
  return myDist;
}

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
    std::vector<double> myVec(10, 1.);

    // check if correct value_type would be deduced
    static_assert(
        std::is_same<decltype(Distribution(myVec))::value_type, double>::value,
        "Wrong type deduced from std::vector<double>");

    // make distribution from vector
    auto myDist = Distribution(myVec);

    // check if values are correct
    TEST_ASSERT_IN_RANGE(myDist.mean, 0.99, 1.01,
                         "Wrong mean value for Distribution<double>: ");
    TEST_ASSERT_IN_RANGE(myDist.stddev, -0.01, 0.01,
                         "Wrong stddev value for Distribution<double>: ");
  }

  // now use more complex distribution to check type support for value_type
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