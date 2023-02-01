#include "List.hpp"
#include <algorithm>
#include <iostream>

// you task it to implement the four currently defaulted SMFs below
// according to the needs of this resource owning class

// copy constructor
List::List(const List &other) {
    this->_size = other._size;
    const Node *other_ptr = other._head;
    Node *this_ptr = NULL;
    if (other_ptr != NULL) {
        this->_head = new Node(other_ptr->value);
        this_ptr = this->_head;
        other_ptr = other_ptr->next;
    }
    while (other_ptr != NULL) {
        Node *temp = new Node(other_ptr->value);
        this_ptr->next = temp;

        this_ptr = this_ptr->next;
        other_ptr = other_ptr->next;
    }
}

// move constructor
List::List(List &&other) {
    std::swap(other._size, _size);
    std::swap(other._head, _head);
}

// copy assignment operator
List &List::operator=(const List &other) {
    List temp(other);
    std::swap(temp._size, _size);
    std::swap(temp._head, _head);
    return *this;
}

// move assignment operator
List &List::operator=(List &&other) {
    std::swap(other._size, _size);
    std::swap(other._head, _head);
    return *this;
}
