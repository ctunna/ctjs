#pragma once

#include <vector>

namespace ctjs {
class Value;

class Array {
 public:
  void push(Value value);
  auto operator[](int index) -> Value&;
  auto elements() const -> const std::vector<Value>&;

 private:
  std::vector<Value> elements_;
};
}  // namespace ctjs
