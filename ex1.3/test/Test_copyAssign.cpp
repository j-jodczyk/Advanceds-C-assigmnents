#include <cstddef>
#include <cstdlib>
#include <string>
#include <List.hpp>

#include "testasserts.hpp"

int main() {
  constexpr std::size_t numberOfElements = 42;
  constexpr List::value_type value = 1.6180;

  List origList(numberOfElements, value);
  origList.push_front(3.1415); // add extra element
  const List &list = origList;
  const auto originalData = list.data();
  const auto originalSize = list.size();

  List newList(numberOfElements / 2, value / 2.); // construct with some data
  newList = list;                                 // copy assign from old list

  // check validity of new list
  TEST_ASSERT(newList.data() != originalData,
              "Data was moved from old list instead of copied");
  TEST_ASSERT(newList.size() == originalSize, "New list has wrong size");

  // check validity of old list
  TEST_ASSERT(list.data() == originalData, "Old list has changed during copy");
  TEST_ASSERT(list.data() != nullptr,
              "Old list has invalid data reference after copy");
  TEST_ASSERT(list.size() == originalSize, "Old list has new size " +
                                               std::to_string(list.size()) +
                                               " after copy");

  // check if they are equal after copy
  {
    auto newElement = newList.data();
    auto oldElement = list.data();
    std::size_t counter = 0;
    while (newElement != nullptr && oldElement != nullptr) {
      TEST_ASSERT(newElement->value == oldElement->value,
                  "New list and old list have different values: " +
                      std::to_string(newElement->value) +
                      " != " + std::to_string(oldElement->value));
      newElement = newElement->next;
      oldElement = oldElement->next;
      ++counter;
    }
    TEST_ASSERT(counter == originalSize, "List has wrong size after copy");
  }

  return EXIT_SUCCESS;
}