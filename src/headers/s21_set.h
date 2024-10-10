#ifndef CPP2_S21_CONTAINERS_SET_H_
#define CPP2_S21_CONTAINERS_SET_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename Key>

class set {
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  class iterator {
   private:
    set* node_{nullptr};

    void root() {
      while (node_->parent_ != nullptr) {
        node_ = node_->parent_;
      }
    }

   public:
    iterator() {}
    iterator(set* node) { node_ = node; }
    ~iterator() { node_ = nullptr; }

    Key operator*() {
      Key answer = {};

      if (std::is_same_v<Key, int> && !node_->data_) {
        root();
        answer = node_->size();

      } else if (node_->data_) {
        answer = *node_->data_;
      } else {
        throw std::invalid_argument("There is no such element");
      }

      return answer;
    }

    void operator++() {
      if (node_->right_ != nullptr) {
        node_ = node_->right_;
        min_data();

      } else if (node_->data_ != nullptr) {
        Key data = *node_->data_;
        while (data >= *node_->data_) {
          node_ = node_->parent_;
        }
      } else {
        node_ = node_->parent_;
      }
    }

    void operator--() {
      if (node_->left_ != nullptr) {
        node_ = node_->left_;
        max_data();

      } else if (node_->data_ != nullptr) {
        printf("111\n");
        Key data = *node_->data_;
        while (data <= *node_->data_) {
          node_ = node_->parent_;
        }
      } else {
        printf("!!!\n");
        node_ = node_->parent_;
      }
    }

    bool operator==(const iterator& other) {
      bool answer = false;

      if (node_ == other.node_) {
        answer = true;
      }

      return answer;
    };

    bool operator!=(const iterator& other) {
      bool answer = false;

      if (node_ != other.node_) {
        answer = true;
      }

      return answer;
    };

    void min_data() {
      while (node_->left_ != nullptr && node_->left_->data_ != nullptr) {
        node_ = node_->left_;
      }
    }

    void max_data() {
      while (node_->right_ != nullptr && node_->right_->data_ != nullptr) {
        node_ = node_->right_;
      }
    }

    void clear_0_set() {
      if (node_->parent_) {
        iterator it(node_->parent_);
        set* end = nullptr;

        if (node_->left_) {
          end = node_->left_;
        } else if (node_->right_) {
          end = node_->right_;
        }

        if (it.node_->left_ == node_) {
          node_->left_ = nullptr;
          delete it.node_->left_;
          it.node_->left_ = end;

        } else {
          node_->right_ = nullptr;
          delete it.node_->right_;
          it.node_->right_ = end;
          if (end) {
            end->parent_ = it.node_;
          }
        }

      } else {
        node_->clear();
      }
    }

    void clear_1_set(set* child, bool left) {
      if (parenthood()) {
        if (left) {
          node_->left_->left_ = nullptr;
          delete node_->left_;
          node_->left_ = child;
        } else {
          node_->right_->right_ = nullptr;
          delete node_->right_;
          node_->right_ = child;
        }

        if (!left || child->data_ != nullptr) {
          child->parent_ = node_;
        }

      } else {
        set* end = node_->end().node_;
        node_->left_ = nullptr;
        node_->right_ = nullptr;

        node_->swap(*child);
        delete child;

        if (left) {
          max_data();
          node_->right_ = end;
          end->parent_ = node_;
        } else {
          min_data();
          node_->left_ = end;
        }

        node_->parent_ = nullptr;
      }
    }

    void clear_2_set(set* child) {
      iterator it = child->begin();
      *node_->data_ = *it.node_->data_;
      node_->erase(it);
    }

    set* get_left() { return node_->left_; }
    set* get_right() { return node_->right_; }
    set* get_node() { return node_; }

    void move_left_child() { node_ = node_->left_; }
    void move_right_child() { node_ = node_->right_; }

    bool end_check(set* check) {
      bool answer = false;
      if (!check->data_) {
        answer = true;
      }
      return answer;
    }

    size_type get_size() { return node_->size(); }

    bool parenthood() {
      bool answer = false;

      if (node_->parent_ != nullptr) {
        node_ = node_->parent_;
        answer = true;
      }

      return answer;
    }
  };

 private:
  Key* data_{nullptr};
  set* parent_{nullptr};
  set* left_{nullptr};
  set* right_{nullptr};

  set(Key data, set* parent) {
    data_ = new Key(data);
    parent_ = parent;
  }

  std::pair<iterator, bool> insert_end() {
    right_ = new set();
    left_ = right_;
    right_->parent_ = this;

    return {this, true};
  }

  std::pair<iterator, bool> insert_child(set** child, const Key& value) {
    *child = new set(value, this);

    return {*child, true};
  }

  void substitution(set* child, const Key& value) {
    set new_child(value, this);
    new_child.right_ = child;
    child = new_child;
  }

  void additional_merge(set* other) {
    if (left_ && left_->data_) {
      left_->additional_merge(other);
    }
    if (right_ && right_->data_) {
      right_->additional_merge(other);
    }

    other->insert(*data_);
  }

 public:
  set() {}

  set(std::initializer_list<Key> const& items) {
    for (const auto& item : items) {
      this->insert(item);
    }
  }

  set(const set& s) { copying_set(s); }

  set(set&& s) {
    data_ = s.data_;
    left_ = s.left_;
    right_ = s.right_;

    s.data_ = nullptr;
    s.parent_ = nullptr;
    s.left_ = nullptr;
    s.right_ = nullptr;

    left_->parent_ = this;
    right_->parent_ = this;
  }

  ~set() {
    if (size()) {
      clear();
    }
  }

  void operator=(set&& s) {
    data_ = s.data_;
    left_ = s.left_;
    right_ = s.right_;

    s.data_ = nullptr;
    s.parent_ = nullptr;
    s.left_ = nullptr;
    s.right_ = nullptr;

    left_->parent_ = this;
    right_->parent_ = this;
  }

  iterator begin() {
    iterator it(this);
    it.min_data();

    return it;
  }

  iterator end() {
    iterator it(this);
    it.max_data();
    ++it;

    return it;
  }

  bool empty() {
    bool answer = false;
    if (data_ == nullptr) {
      answer = true;
    }

    return answer;
  }

  size_type size() {
    size_type answer = 0;

    if (data_ != nullptr) {
      answer = 1;

      if (left_ != nullptr) {
        answer += left_->size();
      }

      if (right_ != nullptr) {
        answer += right_->size();
      }
    }

    return answer;
  }

  size_type max_size() { return std::numeric_limits<size_type>::max(); }

  void clear() {
    if (left_ != nullptr && left_->data_ != nullptr) {
      delete left_;
      left_ = nullptr;
    }

    if (right_ != nullptr) {
      delete right_;
      right_ = nullptr;
    }

    delete data_;
    data_ = nullptr;
  }

  std::pair<iterator, bool> insert(const Key& value) {
    iterator it(this);
    bool insertion = false;

    std::pair<iterator, bool> answer(it, insertion);

    if (data_ == nullptr) {
      data_ = new Key(value);
      answer.second = true;
      insert_end();

    } else if (value < *data_) {
      if (left_ == nullptr) {
        answer = insert_child(&left_, value);
      } else if (left_->data_ == nullptr) {
        set* set_end = left_;
        answer = insert_child(&left_, value);
        left_->left_ = set_end;
      } else {
        answer = left_->insert(value);
      }

    } else if (value > *data_) {
      if (right_ == nullptr) {
        answer = insert_child(&right_, value);
      } else if (right_->data_ == nullptr) {
        set* set_end = right_;
        answer = insert_child(&right_, value);
        right_->right_ = set_end;
        right_->right_->parent_ = right_;
      } else {
        answer = right_->insert(value);
      }
    }

    return answer;
  }

  void erase(iterator pos) {
    if (pos.get_size() == 1) {
      pos.clear_0_set();

    } else if (pos.get_left() && pos.get_right() &&
               !pos.end_check(pos.get_left()) &&
               !pos.end_check(pos.get_right())) {
      pos.clear_2_set(pos.get_right());

    } else if (pos.get_left() && !pos.end_check(pos.get_left())) {
      pos.clear_1_set(pos.get_left(), true);

    } else if (pos.get_right() && !pos.end_check(pos.get_right())) {
      pos.clear_1_set(pos.get_right(), false);
    }
  }

  void swap(set& other) {
    Key* tempData = data_;
    data_ = other.data_;
    other.data_ = tempData;

    set* tempParent = parent_;
    parent_ = other.parent_;
    other.parent_ = tempParent;

    set* tempLeft = left_;
    left_ = other.left_;
    other.left_ = tempLeft;

    set* tempRight = right_;
    right_ = other.right_;
    other.right_ = tempRight;

    left_->parent_ = this;
    right_->parent_ = this;
    other.left_->parent_ = &other;
    other.right_->parent_ = &other;
  }

  void merge(set& other) {
    other.additional_merge(this);
    other.clear();
  }

  iterator find(const Key& key) {
    iterator answer(this);
    bool cycle = true;

    while (*answer != key && cycle) {
      if (answer.get_left() && !answer.end_check(answer.get_left()) &&
          key < *answer) {
        answer.move_left_child();

      } else if (answer.get_right() && !answer.end_check(answer.get_right()) &&
                 key > *answer) {
        answer.move_right_child();

      } else if (*answer != key) {
        cycle = false;
      }
    }

    if (*answer != key) {
      answer = end();
    }

    return answer;
  }

  bool contains(const Key& key) {
    bool answer = false;

    if (find(key) != end()) {
      answer = true;
    }

    return answer;
  }

  void copying_set(const set& s) {
    if (s.data_ != nullptr) {
      insert(*s.data_);

      if (s.left_ != nullptr) {
        copying_set(*s.left_);
      }

      if (s.right_ != nullptr) {
        copying_set(*s.right_);
      }
    }
  }

  void print_set() {
    if (left_ != nullptr && left_->data_ != nullptr) {
      left_->print_set();
    }

    std::cout << *data_ << " ";

    if (right_ != nullptr && right_->data_ != nullptr) {
      right_->print_set();
    }

    if (parent_ == nullptr) {
      printf("\n");
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SET_H_