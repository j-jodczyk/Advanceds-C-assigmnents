#include <Vector.hpp>
#include "testasserts.hpp"

int main() {

  // make a Vector object
  Vector vec(7, 1.6180339887);
  // save the original state
  Vector::size_type size = vec.size();
  Vector::value_type* data = vec.data();

  // now move it into a new Vector object
  Vector newVec(std::move(vec));

  // check if original data is still valid
  TEST_ASSERT(vec.data() != data,  "old vector still references the original data");
  TEST_ASSERT(vec.data() == nullptr, "old vector data not set to nullptr after move");
  TEST_ASSERT(vec.size() == 0, "old vector should have size 0 after move");


  // check whether the new data was moved efficiently
  TEST_ASSERT(newVec.data() == data, "data should have been moved into new Vector object");

  // check whether Vector has the correct size
  TEST_ASSERT(newVec.size() == size, "New vector has different size than old vector")

  // check whether the data was copied correctly
  for(std::size_t i = 0; i < vec.size(); ++i) {
    TEST_ASSERT(newVec[i] == 1.6180339887, "Element " + std::to_string(i) + " does not have the correct value");
  }
  
  return 0;
}