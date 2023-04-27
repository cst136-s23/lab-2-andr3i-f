#pragma once

#include <functional>

template <typename T>
class Collection {
public:
  virtual void append(const T & item) = 0;

  virtual void for_each(std::function<void(T&)> fn) const = 0;

  virtual size_t size() const = 0;

  virtual ~Collection() {}
};
