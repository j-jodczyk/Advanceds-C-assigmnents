#include "List.hpp"
#include <cstddef>

List::Node::Node(const List::value_type &val) : value{val} {}

// default constructor
List::List() {}

// user-defined constructor
List::List(size_type count, const value_type &value) {
  for (std::size_t i = 0; i < count; ++i) {
    push_front(value);
  }
}

// destructor
List::~List() {
  while (_size > 0)
    pop_front();
}

// access current number of nodes in list
List::size_type List::size() const { return _size; }

// obtain root element pointer
const List::Node *List::data() const { return _head; }

// access front element
List::value_type &List::front() { return _head->value; }

// push new list element at the front
void List::push_front(const value_type &value) {
  Node *next_head = new Node(value);
  next_head->next = _head;
  _head = next_head;
  ++_size;
}

// pop element at the front
void List::pop_front() {
  if (_head != nullptr) {
    Node *old_head = _head;
    _head = old_head->next;
    delete old_head;
    --_size;
  }
}