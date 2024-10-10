#ifndef CPP2_S21_CONTAINERS_S21_STACK_H_
#define CPP2_S21_CONTAINERS_S21_STACK_H_

#include <iostream>

namespace s21 {

template <typename T>

class stack {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  struct data {
    value_type* value{};
    data* next = nullptr;
  };

 private:
  data* element_stack;
  size_type iter = 0;

 public:
  stack() {
    element_stack = new data;
    element_stack->value = new value_type;
  }

  stack(std::initializer_list<value_type> const& values) {
    element_stack = new data;
    element_stack->value = new value_type;
    for (const auto value : values) {
      push(value);
    }
  }

  stack(const stack& s) {
    data* temp_element = s.element_stack;
    stack<value_type> ad_st;

    for (size_type i = 0; i < s.iter; i++) {
      ad_st.push(*temp_element->value);
      if (i != s.iter - 1) temp_element = temp_element->next;
    }
    element_stack = new data;
    element_stack->value = new value_type;

    for (size_type i = 0; i < s.iter; i++) {
      push(*ad_st.element_stack->value);
      if (i != s.iter - 1) ad_st.pop();
    }
  }  // Copy

  stack(stack&& s) { func_move(std::move(s)); }  // Move

  ~stack() {
    for (; iter > 0;) {
      pop();
    }
    element_stack = nullptr;
  }

  stack& operator=(stack&& s) {
    func_move(std::move(s));
    return *this;
  }  // Overload operator =

  const_reference top() { return *element_stack->value; }

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
      delete element_stack->value;
      delete element_stack;
      element_stack = temp_element;
    } else {
      temp_element->next = element_stack;
    }
    element_stack = temp_element;

    iter++;
  }

  void pop() {
    if (!empty()) {
      data* temp_element = element_stack;
      element_stack = element_stack->next;

      delete temp_element->value;
      delete temp_element;

      iter--;
    }
  }

  void swap(stack& other) {
    int temp_iter = 0;

    data* temp_element = element_stack;
    temp_iter = iter;
    element_stack = other.element_stack;
    iter = other.iter;
    other.element_stack = temp_element;
    other.iter = temp_iter;
  }

  void func_move(stack&& s) {
    element_stack = s.element_stack;
    iter = s.iter;
    s.element_stack = nullptr;
    s.iter = 0;
  }
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_S21_STACK_H_