#pragma once

#include <cstddef>

class List {
public:
  using value_type = double;
  using size_type = std::size_t;

  // nested class
  struct Node {
    value_type value;
    Node *next = nullptr;
    Node(const value_type &);
  };

private:
  Node *_head = nullptr; // root element
  size_type _size = 0;   // current number of nodes in list

public:
  List();                              // default ctor
  List(size_type, const value_type &); // custom ctor
  ~List();                             // dtor

  List(const List &);            // copy ctor
  List(List &&);                 // move ctor
  List &operator=(const List &); // copy assign
  List &operator=(List &&);      // move assignmassignent

  size_type size() const;              // access current number of nodes in list
  const Node *data() const;            // obtain root element pointer
  value_type &front();                 // access front element
  void push_front(const value_type &); // push new list element at the front
  void pop_front();                    // pop element at the front
};