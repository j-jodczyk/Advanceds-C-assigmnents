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

  // call move constructor
  List newList = std::move(list);

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
  TEST_ASSERT(list.data() == nullptr,
              "Old list has invalid data reference after move");
  TEST_ASSERT(list.size() == 0, "Old list has non-zero size " +
                                    std::to_string(list.size()) +
                                    " after move");

  return EXIT_SUCCESS;
}