#pragma once

#include <vector>

#include "object.h"

namespace ctjs {
class Value;

class Array : public Object {
 public:
  auto push(Value value) -> void;
  auto operator[](const size_t index) -> Value;
  auto size() const -> size_t;
  auto to_string() const -> std::string;

 private:
  size_t size_;
};
}  // namespace ctjs
