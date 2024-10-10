#ifndef CPP2_S21_CONTAINERS_QUEUE_H_
#define CPP2_S21_CONTAINERS_QUEUE_H_

#include <iostream>

namespace s21 {

template <typename T>

class queue {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  struct data {
    value_type* value{};
    data* next = nullptr;
  };

 private:
  data* element_queue;
  data* last_element;
  size_type iter = 0;

 public:
  queue() {
    element_queue = new data;
    element_queue->value = new value_type;
  }

  queue(std::initializer_list<value_type> const& values) {
    element_queue = new data;
    element_queue->value = new value_type;
    for (const auto value : values) {
      push(value);
    }
  }

  queue(const queue& s) {
    data* temp_element = s.element_queue;
    element_queue = new data;
    element_queue->value = new value_type;

    for (size_type i = 0; i < s.iter; i++) {
      push(*temp_element->value);
      if (i != s.iter - 1) temp_element = temp_element->next;
    }
  }  // Copy

  queue(queue&& s) { func_move(std::move(s)); }  // Move

  ~queue() {
    for (; iter > 0;) {
      pop();
    }
    element_queue = nullptr;
    last_element = nullptr;
  }

  queue& operator=(queue&& s) {
    func_move(std::move(s));
    return *this;
  }  // Overload operator =

  const_reference front() { return *element_queue->value; }

  const_reference back() { return *last_element->value; }

  bool empty() {
    bool answer = 1;
    if (size()) answer = 0;
    return answer;
  }

  size_type size() { return iter; }

  void push(const_reference n) {
    data* temp_element = new data;
    temp_element->value = new value_type(n);

    if (!iter) {
      delete element_queue->value;
      delete element_queue;
      element_queue = temp_element;
    } else {
      last_element->next = temp_element;
    }
    last_element = temp_element;

    iter++;
  }

  void pop() {
    if (!empty()) {
      data* temp_element = element_queue;
      element_queue = element_queue->next;

      temp_element->next = nullptr;
      delete temp_element->value;
      delete temp_element;

      iter--;
    }
  }

  void swap(queue& other) {
    int temp_iter = 0;

    data* temp_element = element_queue;
    temp_iter = iter;
    element_queue = other.element_queue;
    iter = other.iter;
    other.element_queue = temp_element;
    other.iter = temp_iter;
  }

  void func_move(queue&& s) {
    element_queue = s.element_queue;
    last_element = s.last_element;
    iter = s.iter;
    s.element_queue = nullptr;
    s.last_element = nullptr;
    s.iter = 0;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_QUEUE_H_