#ifndef CPP2_S21_CONTAINERS_MAP_H_
#define CPP2_S21_CONTAINERS_MAP_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename Key, typename T>

class map {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  class iterator {
   private:
    map* node_{nullptr};

    void root() {
      while (node_->parent_ != nullptr) {
        node_ = node_->parent_;
      }
    }

   public:
    iterator() {}
    iterator(map* node) { node_ = node; }
    ~iterator() { node_ = nullptr; }

    mapped_type operator*() {
      if (!node_->data_) {
        throw std::invalid_argument("There is no such element");
      }
      return node_->data_->second;
    }

    void operator++() {
      if (node_->right_ != nullptr) {
        node_ = node_->right_;
        min_data();

      } else if (node_->data_ != nullptr) {
        Key data = node_->data_->first;
        while (data >= node_->data_->first) {
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
        Key data = node_->data_->first;
        while (data <= node_->data_->first) {
          node_ = node_->parent_;
        }
      } else {
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
        node_->left_ = nullptr;
        node_->right_ = nullptr;

        std::pair<map*, bool> par_chil = get_parent_child();

        if (par_chil.second) {
          delete par_chil.first->left_;
          par_chil.first->left_ = nullptr;
        } else {
          delete par_chil.first->right_;
          par_chil.first->right_ = nullptr;
        }
      }
    }

    void clear_1_set(map* child, bool left) {
      std::pair<map*, bool> par_chil = get_parent_child();
      clear_0_set();

      if (!left || child->data_) {
        child->parent_ = par_chil.first;
      }

      if (par_chil.second) {
        par_chil.first->left_ = child;
      } else {
        par_chil.first->right_ = child;
      }
    }

    void clear_2_set() {
      map* temp_map = node_;

      if (node_->left_->data_) {
        node_ = node_->left_;
        max_data();
      } else {
        node_ = node_->right_;
        min_data();
      }

      temp_map->data_->second = node_->data_->second;

      temp_map->erase(*this);
    }

    map* get_left() { return node_->left_; }
    map* get_right() { return node_->right_; }
    map* get_node() { return node_; }

    std::pair<map*, bool> get_parent_child() {
      map* parent = node_->parent_;
      std::pair<map*, bool> answer(parent, true);

      if (parent->right_ == node_) {
        answer.second = false;
      }

      return answer;
    }

    const Key first() {
      if (!node_->data_) {
        throw std::invalid_argument("There is no such element");
      }
      return node_->data_->first;
    }

    T& second() {
      if (!node_->data_) {
        throw std::invalid_argument("There is no such element");
      }
      return node_->data_->second;
    }

    void move_left_child() { node_ = node_->left_; }
    void move_right_child() { node_ = node_->right_; }

    bool end_check(map* check) {
      bool answer = false;
      if (!check->data_) {
        answer = true;
      }
      return answer;
    }

    size_type get_size() { return node_->size(); }
  };

 private:
  value_type* data_{nullptr};
  map* parent_{nullptr};
  map* left_{nullptr};
  map* right_{nullptr};

  map(value_type data, map* parent) {
    data_ = new value_type(data);
    parent_ = parent;
  }

  std::pair<iterator, bool> insert_end() {
    right_ = new map();
    left_ = right_;
    right_->parent_ = this;

    return {this, true};
  }

  std::pair<iterator, bool> insert_child(map** child, const_reference value) {
    *child = new map(value, this);

    return {*child, true};
  }

  void additional_merge(map* other) {
    if (left_ && left_->data_) {
      left_->additional_merge(other);
    }
    if (right_ && right_->data_) {
      right_->additional_merge(other);
    }

    other->insert(*data_);
  }

 public:
  map() {}

  map(std::initializer_list<value_type> const& items) {
    for (const_reference item : items) {
      insert(item);
    }
  }

  map(const map& m) { copying_set(m); }

  map(map&& m) {
    data_ = m.data_;
    left_ = m.left_;
    right_ = m.right_;

    m.data_ = nullptr;
    m.parent_ = nullptr;
    m.left_ = nullptr;
    m.right_ = nullptr;

    left_->parent_ = this;
    right_->parent_ = this;
  }

  ~map() {
    if (size()) {
      clear();
    }
  }

  void operator=(map&& m) {
    data_ = m.data_;
    left_ = m.left_;
    right_ = m.right_;

    m.data_ = nullptr;
    m.parent_ = nullptr;
    m.left_ = nullptr;
    m.right_ = nullptr;

    left_->parent_ = this;
    right_->parent_ = this;
  }

  T& operator[](const Key& key) { return at(key); }

  T& at(const Key& key) {
    iterator it(this);
    bool cycle = true;

    while (it.first() != key && cycle) {
      if (it.get_left() && !it.end_check(it.get_left()) && key < it.first()) {
        it.move_left_child();

      } else if (it.get_right() && !it.end_check(it.get_right()) &&
                 key > it.first()) {
        it.move_right_child();

      } else if (it.first() != key) {
        cycle = false;
      }
    }

    if (it.first() != key) {
      throw std::invalid_argument("There is no such element");
    }

    return it.second();
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

  std::pair<iterator, bool> insert(const value_type& value) {
    iterator it(this);
    bool insertion = false;

    std::pair<iterator, bool> answer(it, insertion);

    if (data_ == nullptr) {
      data_ = new value_type(value);
      answer.second = true;
      insert_end();

    } else if (value.first < data_->first) {
      if (left_ == nullptr) {
        answer = insert_child(&left_, value);
      } else if (left_->data_ == nullptr) {
        map* set_end = left_;
        answer = insert_child(&left_, value);
        left_->left_ = set_end;
      } else {
        answer = left_->insert(value);
      }

    } else if (value.first > data_->first) {
      if (right_ == nullptr) {
        answer = insert_child(&right_, value);
      } else if (right_->data_ == nullptr) {
        map* set_end = right_;
        answer = insert_child(&right_, value);
        right_->right_ = set_end;
        right_->right_->parent_ = right_;
      } else {
        answer = right_->insert(value);
      }
    }

    return answer;
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return insert(std::pair<Key, T>(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    std::pair<iterator, bool> answer = insert(std::pair<Key, T>(key, obj));

    if (!answer.second) {
      iterator it = answer.first;
      it.second() = obj;
    }

    return answer;
  }

  void erase(iterator pos) {
    if (pos.get_node() == this && !left_->data_ && !right_->data_) {
      clear();
    } else if (!pos.get_left() && !pos.get_right()) {
      pos.clear_0_set();
    } else if (pos.get_left() && pos.get_right()) {
      pos.clear_2_set();
    } else if (pos.get_left()) {
      pos.clear_1_set(pos.get_left(), true);
    } else if (pos.get_right()) {
      pos.clear_1_set(pos.get_right(), false);
    }
  }

  void swap(map& other) {
    value_type* tempData = data_;
    data_ = other.data_;
    other.data_ = tempData;

    map* tempParent = parent_;
    parent_ = other.parent_;
    other.parent_ = tempParent;

    map* tempLeft = left_;
    left_ = other.left_;
    other.left_ = tempLeft;

    map* tempRight = right_;
    right_ = other.right_;
    other.right_ = tempRight;

    left_->parent_ = this;
    right_->parent_ = this;
    other.left_->parent_ = &other;
    other.right_->parent_ = &other;
  }

  void merge(map& other) {
    other.additional_merge(this);
    other.clear();
  }

  bool contains(const Key& key) {
    bool answer = true;

    try {
      at(key);
    } catch (const std::exception& e) {
      answer = false;
    }

    return answer;
  }

  void copying_set(const map& m) {
    if (m.data_ != nullptr) {
      insert(*m.data_);

      if (m.left_ != nullptr) {
        copying_set(*m.left_);
      }

      if (m.right_ != nullptr) {
        copying_set(*m.right_);
      }
    }
  }

  void print_map() {
    if (left_ != nullptr && left_->data_ != nullptr) {
      left_->print_map();
    }

    std::cout << data_->second << " ";

    if (right_ != nullptr && right_->data_ != nullptr) {
      right_->print_map();
    }

    if (parent_ == nullptr) {
      printf("\n");
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MAP_H_