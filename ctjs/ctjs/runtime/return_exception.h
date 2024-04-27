#pragma once

#include <utility>

#include "ctjs/runtime/value.h"

namespace ctjs {
class ReturnException : public std::exception {
 public:
  explicit ReturnException(Value value) : value_(std::move(value)) {}

  [[nodiscard]] auto value() const -> Value { return value_; }

 private:
  Value value_;
};
}  // namespace ctjs
