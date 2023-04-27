#pragma once

#include "collection.h"

template <typename T>
class Vector : public Collection<T> {
public:
  Vector() = default;

  ~Vector() {
    delete[] items;
    items = nullptr;
    len = 0;
  }

  Vector(const Vector<T> & other) {
    for (size_t i{}; i < other.len; ++i) {
      append(other.items[i]);
    }
  }

  Vector<T> & operator=(const Vector<T> & other) {
    if (this == &other) {
      return *this;
    }

    delete[] items;
    for (size_t i{}; i < other.len; ++i) {
      append(other.items[i]);
    }

    return *this;
  }

  size_t size() const override { return len; }

  void append(const T & item) override {
    T * newItems = new T[len +1]{};

    for (size_t i{}; i < len; ++i) {
      newItems[i] = items[i];
    }
    newItems[len] = item;

    ++len;
    delete[] items;
    items = newItems;
  }

  void for_each(std::function<void(T&)> fn) const override {
    for (size_t i{}; i < len; ++i) {
      fn(items[i]);
    }
  }

private:
  size_t len{};
  T * items{};
};
