#include <cstddef>
#include <cstdlib>
#include <string>
#include <List.hpp>
#include "testasserts.hpp"

int main() {
  constexpr std::size_t numberOfElements = 42;
  constexpr List::value_type value = 1.6180;

  List list(numberOfElements, value);
  list.push_front(3.1415); // add extra element
  const auto originalData = list.data();
  const auto originalSize = list.size();

  List newList(numberOfElements,
               value / 2.);  // default construct new List object
  newList = std::move(list); // invoking move-assign

  // check validity of new list
  TEST_ASSERT(newList.data() == originalData,
              "Data was not moved from old list");
  TEST_ASSERT(newList.size() == originalSize, "Size was changed during move");
  {
    std::size_t counter = 1;
    auto currentElement = newList.data();
    // check first element
    TEST_ASSERT(currentElement->value == 3.1415,
                "First element is wrong after move")
    currentElement = currentElement->next;
    while (currentElement != nullptr) {
      TEST_ASSERT(currentElement->value == value,
                  "Values of list have changed during move");
      currentElement = currentElement->next;
      ++counter;
    }
    TEST_ASSERT(counter == originalSize, "List has wrong size after move");
  }

  // check validity of old list
  TEST_ASSERT(list.data() != originalData,
              "Old list still holds reference to the moved data");

  // check if old list is valid (size equals number of nodes)
  {
    std::size_t counter = 0;
    auto currentElement = list.data();
    while (currentElement != nullptr) {
      currentElement = currentElement->next;
      ++counter;
    }
    TEST_ASSERT(counter == list.size(), "List has invalid state after move");
  }

  // check if old list is in a destructible state (not leaks on desctruction)
  // Cannot check this in an assert, address sanitizer will detect this at
  // runtime

  return EXIT_SUCCESS;
}