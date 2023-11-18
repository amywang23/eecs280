#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the numElements
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    return numElements;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node* n = new Node{};
    n->datum = datum;
    n->next = first;
    n->prev = nullptr;
    if (empty()) {
      first = n;
      last = n;
    }
    else {
      first->prev = n;
      first = n;
    }
    

    numElements++;

  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node* n = new Node{};
    n->datum = datum;
    n->next = nullptr;
    n->prev = last;
    if (last) {
      last->next = n;
    }
    if (size() == 0) {
      first = n;
    }
    last = n;
    numElements++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(numElements != 0);
    if (numElements == 1) {
      delete first;
      first = nullptr;
      last = nullptr;

    }
    else {
      Node *tmp = first;
      first = first->next;
      first->prev = nullptr;  // Update the prev pointer of the new first node
      delete tmp;
    }
    numElements--;
    if (numElements == 1) {
      last = first;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(numElements != 0);
    if (numElements == 1) {
      delete first;
      first = nullptr;
      last = nullptr;
    }
    else {
      Node *tmp = last;
      last = last -> prev;
      last -> next = nullptr;
      delete tmp;
    }
    numElements--;

    if (numElements == 1) {
      last = first;
    }
    
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while (numElements != 0) {
      pop_front();
    }
  }

  List():
    first(nullptr), last(nullptr), numElements(0) {

  }

  ~List() {
    clear();
  }

  List(const List<T>& otherList): first(nullptr), last(nullptr), numElements(0) {
    copy_all(otherList);
  }

  List<T>& operator=(const List<T>& rhs) {
    if (this == &rhs) {
      return *this;
    }
    copy_all(rhs);
    return *this;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    clear();
    for (Node* ptr = other.first; ptr != nullptr; ptr = ptr->next) {
      push_back(ptr->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

  int numElements;

public:
  ////////////////////////////////////////
  class Iterator {
    
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T& operator*() {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(const Iterator& x) const {
      return (node_ptr == x.node_ptr);
    }

    bool operator!=(const Iterator& x) const {
      return (node_ptr != x.node_ptr);
    }


    Iterator():node_ptr(nullptr) {
      
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p): node_ptr(p) {

    }

  };
  //List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
    // works because friend declaration
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
    // nullptr
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {

    if (i.node_ptr == first) {
      pop_front();
    }
    else if (i.node_ptr == last) {
      pop_back();
    }
    else {
      i.node_ptr->prev->next = i.node_ptr->next;
      if (i.node_ptr -> next != nullptr){
        i.node_ptr -> next -> prev = i.node_ptr -> prev;
      }
      delete i.node_ptr;
      numElements--;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    if (i.node_ptr == first) {
      push_front(datum);
      return;
    }
    else if (i == end()) {
      push_back(datum);
      return;
    }
    Node* n = new Node{};
    n->datum = datum;
    n->next = i.node_ptr;
    n->prev = i.node_ptr->prev;

    i.node_ptr->prev->next = n;
    i.node_ptr->prev = n;
    
    numElements++;
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.