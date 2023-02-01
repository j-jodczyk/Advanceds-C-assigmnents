#include <Vector.hpp>
#include "testasserts.hpp"

int main() {

  // make a Vector object
  Vector vec(7, 1.6180339887);
  // save the original state
  Vector::size_type size = vec.size();
  Vector::value_type* data = vec.data();

  // now copy it into a new Vector object
  Vector newVec(vec);

  // check if original data is still unchanged
  TEST_ASSERT(data == vec.data(), "Original data has changed during copy");

  // check that original size is still the same
  TEST_ASSERT(size == vec.size(), "Original vector has changed in size during copy");

  // check whether the data was really copied
  TEST_ASSERT(vec.data() != newVec.data(), "Data should not alias");

  // check whether Vector has the correct size
  TEST_ASSERT(vec.size() == newVec.size(), "New vector has different size than old vector")

  // check whether the data was copied correctly
  for(std::size_t i = 0; i < vec.size(); ++i) {
    TEST_ASSERT(vec[i] == newVec[i], "Element " + std::to_string(i) + " does not have the correct value");
  }
  
  return 0;
}