#ifndef CPP2_S21_CONTAINERS_LIST_NODE_H_
#define CPP2_S21_CONTAINERS_LIST_NODE_H_

namespace s21 {
template <typename T>
class list;

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename T>
struct ListNode {
  T value_ = T();
  ListNode* next_ = nullptr;
  ListNode* prev_ = nullptr;
  explicit ListNode(T value = T(), ListNode* next = nullptr,
                    ListNode* prev = nullptr)
      : value_(value), next_(next), prev_(prev) {}
};
};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_LIST_NODE_H_