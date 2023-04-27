#pragma once

#include "collection.h"

template <typename T>
struct Node {
  T data;
  Node * next;
};

template <typename T>
class List : public Collection<T> {
public:
  List() = default;

  ~List() {
    Node<T> * cur{head};
    while (cur) {
      Node<T> * temp = cur;
      cur = temp->next;
      delete temp;
    }

    head = nullptr;
    tail = nullptr;
    len = 0;
  }

  List(const List<T> & other) {
    Node<T> * cur = other.head;
    while (cur) {
      append(cur->data);
      cur = cur->next;
    }
  }

  List<T> & operator=(const List<T> & other) {
    if (this == &other) {
      return *this;
    }

    Node<T> * cur{head};
    while (cur) {
      Node<T> * temp = cur;
      cur = temp->next;
      delete temp;
    }

    head = nullptr;
    tail = nullptr;
    len = 0;

    cur = other.head;
    while (cur) {
      append(cur->data);
      cur = cur->next;
    }

    return *this;
  }

  size_t size() const override { return len; }

  void append(const T & item) override {
    Node<T> * node = new Node<T>{item};

    if (!head) {
      head = node;
      tail = node;
    } else {
      tail->next = node;
      tail = node;
    }

    ++len;
  }

  void for_each(std::function<void(T&)> fn) const override {
    Node<T> * cur = head;

    while (cur) {
      fn(cur->data);
      cur = cur->next;
    }
  }

private:
  Node<T> * head{};
  Node<T> * tail{};
  size_t len{};
};
