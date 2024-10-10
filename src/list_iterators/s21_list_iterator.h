#ifndef CPP2_S21_CONTAINERS_LIST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_LIST_ITERATOR_H_

#include "../headers/s21_list.h"
#include "../headers/s21_list_node.h"

namespace s21 {
template <typename T>
class ListIterator {
  friend class list<T>;
  friend class ListConstIterator<T>;
  using pointer = ListNode<T>*;

  pointer node_ = nullptr;
  pointer prev_ = nullptr;
  pointer next_ = nullptr;
  void comparePointers() {
    if (node_ != nullptr) {
      prev_ = node_->prev_;
      next_ = node_->next_;
    }
  }
  explicit ListIterator(const pointer node) : node_(node) { comparePointers(); }

 public:
  ListIterator(){};

  ListIterator(const ListIterator& other) { operator=(other); }

  ListIterator& operator=(const ListIterator& other) {
    node_ = other.node_;
    comparePointers();
    return *this;
  }

  ListIterator& operator++() {
    if (next_ != nullptr) {
      node_ = next_;
      comparePointers();
    }
    return *this;
  }

  ListIterator& operator--() {
    if (next_ == nullptr) {
      comparePointers();
    }
    if (prev_ != nullptr) {
      node_ = prev_;
      comparePointers();
    }
    return *this;
  }
  T& operator*() { return node_->value_; }
  T* operator->() { return &(node_->value_); }

  bool operator==(const ListIterator& other) { return node_ == other.node_; }
  bool operator!=(const ListIterator& other) { return node_ != other.node_; }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_LIST_ITERATOR_H_