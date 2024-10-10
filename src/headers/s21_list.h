#ifndef CPP2_S21_CONTAINERS_LIST_H_
#define CPP2_S21_CONTAINERS_LIST_H_

#include <limits>

#include "../list_iterators/s21_const_list_iterator.h"
#include "../list_iterators/s21_list_iterator.h"
#include "s21_list_node.h"

namespace s21 {

template <class T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;
  using pointer = ListNode<T>*;

  list() : end_(new ListNode(value_type())){};

  list(size_type n) : list() {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (auto const& item : items) {
      push_back(item);
    }
  }

  list(const list& l) : list() {
    if (this != &l) {
      clear();
      for (const_iterator it = l.begin(); it != l.end(); ++it) {
        push_back(*it);
      }
    }
  }

  list(list&& l) : list() { operator=(std::move(l)); }

  ~list() {
    clear();
    delete end_;
  }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();
      first_ = l.first_;
      last_ = l.last_;
      size_ = l.size_;
      end_->prev_ = last_;
      if (last_ != nullptr) last_->next_ = end_;
      l.first_ = nullptr;
      l.last_ = nullptr;
      l.end_->prev_ = nullptr;
      l.size_ = 0;
    }
    return *this;
  }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max)() / sizeof(ListNode<T>) / 2;
  }

  iterator begin() {
    if (size_ == 0) return iterator(end_);
    return iterator(first_);
  }

  const_iterator begin() const {
    if (size_ == 0) return const_iterator(end_);
    return const_iterator(first_);
  }
  iterator end() { return iterator(end_); }

  const_iterator end() const { return const_iterator(end_); }

  const_reference front() const {
    if (first_ == nullptr) throw "list is empty";
    return first_->value_;
  }

  const_reference back() const {
    if (last_ == nullptr) throw "list is empty";
    return last_->value_;
  }

  iterator insert(iterator pos, const_reference value) {
    if (size_ + 1 > max_size()) throw "list is full";
    auto resIter = iterator();
    if (pos.node_ == end_) {
      if (last_ == nullptr) {
        last_ = new ListNode<value_type>(value);
        first_ = last_;
        resIter = iterator(last_);
      } else {
        last_->next_ = new ListNode<value_type>(value);
        last_->next_->prev_ = last_;
        last_ = last_->next_;
        resIter = iterator(last_);
      }
      last_->next_ = end_;
      end_->prev_ = last_;
    } else if (pos.node_ == first_) {
      first_->prev_ = new ListNode<value_type>(value);
      first_->prev_->next_ = first_;
      first_ = first_->prev_;
      resIter = iterator(first_);
    } else {
      auto Node = new ListNode<value_type>(value);
      Node->next_ = pos.node_;
      Node->prev_ = pos.node_->prev_;
      Node->next_->prev_ = Node;
      Node->prev_->next_ = Node;
      resIter = iterator(Node);
    }
    size_++;
    return resIter;
  }
  void push_back(const_reference value) { insert(iterator(end_), value); }
  void push_front(const_reference value) {
    if (empty())
      push_back(value);
    else
      insert(begin(), value);
  }

  void erase(iterator pos) {
    if (!empty() && pos.node_ != end_ && pos.node_ != nullptr) {
      if (size_ == 1) {
        first_ = nullptr;
        last_ = nullptr;
        delete end_->prev_;
        end_->prev_ = nullptr;
      } else {
        if (pos.node_ == first_) {
          first_ = first_->next_;
          delete first_->prev_;
          first_->prev_ = nullptr;
        } else if (pos.node_ == last_) {
          last_ = last_->prev_;
          delete end_->prev_;
          end_->prev_ = last_;
          last_->next_ = end_;
        } else {
          pos.node_->prev_->next_ = pos.node_->next_;
          pos.node_->next_->prev_ = pos.node_->prev_;
          delete pos.node_;
        }
      }
      size_--;
    }
  }

  void pop_back() {
    if (!empty()) erase(iterator(last_));
  }

  void pop_front() {
    if (!empty()) erase(iterator(first_));
  }

  void clear() {
    while (!empty()) {
      pop_back();
    }
    first_ = nullptr;
    last_ = nullptr;
    end_->prev_ = nullptr;
  }

  void swap(list& other) {
    std::swap(first_, other.first_);
    std::swap(last_, other.last_);
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
  }

  void splice(const_iterator pos, list& other) {
    iterator tempIter = iterator(pos.node_);
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      insert(tempIter, *iter);
    }
    other.clear();
  }

  void unique() {
    iterator iter = begin();
    auto elem = *iter;
    ++iter;
    for (; iter != end(); ++iter) {
      if (*iter == elem) {
        erase(iter);
      } else {
        elem = *iter;
      }
    }
  }

  void sort() {
    if (!empty()) {
      auto tmpIter = begin();
      for (auto i = begin(); i != end(); ++i) {
        for (auto j = tmpIter; j != i; ++j) {
          if (*i < *j) {
            std::swap(*i, *j);
          }
        }
      }
    }
  }

  void reverse() {
    if (!empty()) {
      auto tmpIterLeft = begin();
      auto tmpIterRight = end();

      --tmpIterRight;
      for (size_type i = 0; i < size_ / 2; ++i) {
        std::swap(*tmpIterLeft, *tmpIterRight);
        ++tmpIterLeft;
        --tmpIterRight;
      }
    }
  }

  void merge(list& other) {
    if (size_ + other.size_ > max_size()) {
      throw "list is full";
    }
    auto finalList = list(size_ + other.size_);
    iterator thisIterator = begin();
    iterator otherIterator = other.begin();
    iterator finalIterator = finalList.begin();
    while (finalIterator != finalList.end()) {
      if (thisIterator != end() && otherIterator != other.end()) {
        if (*thisIterator <= *otherIterator) {
          *finalIterator = *thisIterator;
          ++thisIterator;
        } else {
          *finalIterator = *otherIterator;
          ++otherIterator;
        }
      } else if (thisIterator != end()) {
        *finalIterator = *thisIterator;
        ++thisIterator;
      } else if (otherIterator != other.end()) {
        *finalIterator = *otherIterator;
        ++otherIterator;
      }
      ++finalIterator;
    }
    clear();
    other.clear();
    *this = list(std::move(finalList));
  }

 private:
  pointer first_ = nullptr;
  pointer last_ = nullptr;
  pointer end_ = nullptr;
  size_type size_ = 0;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_LIST_H_