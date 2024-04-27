#pragma once

#include "object.h"

namespace ctjs {
class Value;

class Array : public Object {
 public:
  auto push(Value value) -> void;
  auto operator[]( size_t index) -> Value;
  [[nodiscard]] auto size() const -> size_t;
  [[nodiscard]] auto to_string() const -> std::string override;

 private:
  size_t size_;
};
}  // namespace ctjs
