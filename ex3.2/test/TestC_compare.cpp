#include "testasserts.hpp"

#include <type_traits>
#include <unique_ptr.hpp>

struct Widget {
  double m = 42;
};

int main() {

  using T = Widget;

  { // compare to same type
    auto up1 = unique_ptr(new T{});
    auto up2 = unique_ptr(new T{});
    TEST_ASSERT(up1 != up2,
                "compare unequal to other unique_ptr not working as expected");
    // construct additional unique_ptr handling the same resource
    auto up3 = unique_ptr(up2.get());
    TEST_ASSERT(up2 == up3,
                "compare equal to other unique_ptr not working as expected");
    // release the ressource so there is no double free
    up3.release();
  }

  { // compare to nullptr
    auto up = unique_ptr(new T{});
    TEST_ASSERT(up != nullptr,
                "compare unequal to nullptr not working as expected");
    up = nullptr;
    TEST_ASSERT(up == nullptr,
                "compare equal to nullptr not working as expected");
  }

  { // use as bool
    auto up = unique_ptr(new T{});
    bool expect_true = up;
    TEST_ASSERT(expect_true == true,
                "implicit conversion to bool not working as expected");
  }
  { // use as bool
    auto up = unique_ptr<T>(nullptr);
    bool expect_false = up;
    TEST_ASSERT(expect_false == false,
                "implicit conversion to bool not working as expected");
  }

  return 0;
}