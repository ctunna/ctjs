#pragma once

#include <vector>

namespace ctjs {
class Value;

class Array {
 public:
  void push(Value value);
  auto operator[](int index) -> Value&;

  auto size() const -> size_t;

  auto begin() -> std::vector<Value>::iterator;
  auto end() -> std::vector<Value>::iterator;

 private:
  std::vector<Value> elements_;
};
}  // namespace ctjs
