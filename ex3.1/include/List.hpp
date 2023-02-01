#pragma once
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>

template <class T> class List {

public:
  using size_type = std::size_t;
  using value_type = T;

// private:

  struct Node {
    Node *prev;
    Node *next;
  };

  struct ValueNode : Node {
    T value;
  };

  Node *entry;
  size_type size;

  void swap(List &other) {
    std::swap(entry, other.entry);
    std::swap(size, other.size);
  }

  void erase(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete static_cast<ValueNode *>(node);
  }

  void append(const List &other) {
    for (const auto &item : other) {
      push_back(item);
    }
  }

public:
  void clear() {
    auto iter = entry->next;
    while (iter != entry) {
      const auto next = iter->next;
      erase(iter);
      iter = next;
    }
  }

  void push_back(const value_type &value) {
    const auto new_node = new ValueNode{entry->prev, entry, value};
    entry->prev->next = new_node;
    entry->prev = new_node;
    ++size;
  }

  void push_front(const value_type &value) {
    const auto new_node = new ValueNode{entry, entry->next, value};
    entry->next->prev = new_node;
    entry->next = new_node;
    ++size;
  }

  List() : size(0) {
    entry = new Node{NULL, NULL};
    entry->prev = entry;
    entry->next = entry;
  };

  List(const List &other) : size(0) {
    entry = new Node{NULL, NULL};
    entry->prev = entry;
    entry->next = entry;
    append(other);
  }

  List(List &&other) : size(0) {
    entry = new Node{NULL, NULL};
    entry->prev = entry;
    entry->next = entry;
    std::swap(entry, other.entry);
    std::swap(size, other.size);
  }

  List &operator=(const List &other) {
    clear();
    append();
    return *this;
  }

  List &operator=(List &&other) {
    std::swap(entry, other.entry);
    std::swap(size, other.size);
    return *this;
  }

  ~List() {
    clear();
    delete entry;
  }

  // ------------ SOLUTION START

public:
  template <typename iter_type> struct ListIterator {
    Node *curr;
    using value_type = iter_type;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = iter_type*;
    using reference = iter_type&;

    value_type &operator*() { return static_cast<ValueNode *>(curr)->value; } // static because it's not polymorfic
    ListIterator operator++() {
      curr = curr->next;
      return *this;
    }
    ListIterator operator--() {
      curr = curr->prev;
      return *this;
    }
    iter_type* operator->() { return &static_cast<ValueNode *>(curr)->value; }
    bool operator==(const ListIterator& other) { return curr == other.curr; }
    bool operator!=(const ListIterator& other) { return curr != other.curr; }
  };

  typedef ListIterator<const T> const_iterator;
  typedef ListIterator<T> iterator;

  iterator begin() {return iterator{entry->next};}
  iterator end() {return iterator{entry};} // because last->next == entry

  const_iterator begin() const {return const_iterator{entry->next};};
  const_iterator end() const {return const_iterator{entry};};
  const_iterator cbegin() const {return const_iterator{entry->next};};
  const_iterator cend() const {return const_iterator{entry};};


  //compatibility with std lib
// ------------ SOLUTION END

};
