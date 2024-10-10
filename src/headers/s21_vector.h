#ifndef CPP2_S21_CONTAINERS_VECTOR_H_
#define CPP2_S21_CONTAINERS_VECTOR_H_

#include <initializer_list>
#include <limits>

namespace s21 {

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  vector() : data_(nullptr), size_(0), capacity_(0){};

  vector(size_type n) : vector() {
    size_ = n;
    capacity_ = n;
    if (size_ > 0) {
      data_ = new value_type[n]();
    }
  }

  vector(std::initializer_list<value_type> const& items) : vector() {
    size_ = items.size();
    capacity_ = items.size();
    if (size_ > 0) {
      data_ = new value_type[size_]();
    }
    std::copy(items.begin(), items.end(), data_);
  }

  vector(const vector& v) : vector() {
    if (this != &v) {
      if (data_ != nullptr) {
        makeEmpty();
      }
      size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = new value_type[size_]();
      std::copy(v.data_, v.data_ + size_, data_);
    }
  }

  vector(vector&& v) : vector() { operator=(std::move(v)); }
  ~vector() {
    if (data_ != nullptr) {
      makeEmpty();
    }
  }

  vector& operator=(vector&& v) {
    if (this != &v) {
      if (data_ != nullptr) {
        makeEmpty();
      }
      size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = v.data_;
      v.data_ = nullptr;
      v.size_ = 0;
      v.capacity_ = 0;
    }
    return *this;
  }

  size_type size() { return size_; }

  size_type capacity() { return capacity_; }

  reference at(size_type pos) { return data_[pos]; }

  const_reference at(size_type pos) const { return data_[pos]; }

  reference operator[](size_type pos) { return at(pos); }

  const_reference operator[](size_type pos) const { return at(pos); }

  iterator begin() { return &data_[0]; }
  iterator end() { return &data_[size_]; }
  bool empty() { return size_ == 0; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(size_type);
  }

  const_reference front() {
    if (empty()) throw "vector is empty";
    return data_[0];
  }

  const_reference back() {
    if (empty()) throw "vector is empty";
    return data_[size_ - 1];
  }

  iterator data() { return data_; }

  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error("Not enough memory");
    }
    if (size >= capacity_) {
      capacity_ = size;
      value_type* newData = data_;
      data_ = new value_type[size]();
      std::copy(newData, newData + size_, data_);
      delete[] newData;
    }
  }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      capacity_ = size_;
      reserve(capacity_);
    }
  }

  void clear() { size_ = 0; }

  void push_back(const_reference value) {
    if (size_ >= capacity_) {
      if (capacity_ == 0)
        reserve(1);
      else
        reserve(capacity_ * 2);
    }
    ++size_;
    data_[size_ - 1] = value;
  }

  void pop_back() { --size_; }

  iterator insert(iterator pos, const_reference value) {
    iterator finalIter = nullptr;
    if (pos == end()) {
      push_back(value);
      finalIter = &data_[size_ - 1];
    } else {
      size_type newElementPosition = std::distance(begin(), pos);
      push_back(value_type());
      value_type temp = data_[newElementPosition];
      data_[newElementPosition] = value;
      for (size_type i = newElementPosition + 1; i < size() - 1; ++i) {
        std::swap(data_[i], temp);
      }
      data_[size_ - 1] = temp;
      finalIter = &data_[newElementPosition];
    }
    return finalIter;
  }

  void erase(iterator pos) {
    if (pos == end()) {
      pop_back();
    } else {
      size_type newElementPosition = std::distance(begin(), pos);
      for (size_type i = newElementPosition; i < size() - 1; ++i) {
        std::swap(data_[i], data_[i + 1]);
      }
      pop_back();
    }
  }

  void swap(vector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

 private:
  iterator data_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;

  void makeEmpty() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_VECTOR_H_