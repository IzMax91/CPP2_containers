#ifndef CPP2_S21_CONTAINERS_CONST_LIST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_CONST_LIST_ITERATOR_H_

#include "../headers/s21_list.h"
#include "../headers/s21_list_node.h"

namespace s21 {
template <typename T>
class ListConstIterator {
  friend class list<T>;
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
  explicit ListConstIterator(const pointer node) : node_(node) {
    comparePointers();
  }

 public:
  ListConstIterator(){};

  ListConstIterator(const ListConstIterator& other) { operator=(other); }

  ListConstIterator(const ListIterator<T>& iter) : node_(iter.node_) {
    comparePointers();
  }

  ListConstIterator& operator=(const ListConstIterator& other) {
    node_ = other.node_;
    comparePointers();
    return *this;
  }

  ListConstIterator& operator++() {
    if (next_ != nullptr) {
      node_ = next_;
      comparePointers();
    }
    return *this;
  }

  ListConstIterator& operator--() {
    if (next_ == nullptr) {
      comparePointers();
    }
    if (prev_ != nullptr) {
      node_ = prev_;
      comparePointers();
    }
    return *this;
  }
  const T& operator*() { return node_->value_; }
  const T* operator->() { return &(node_->value_); }

  bool operator==(const ListConstIterator& other) {
    return node_ == other.node_;
  }
  bool operator!=(const ListConstIterator& other) {
    return node_ != other.node_;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_CONST_LIST_ITERATOR_H_