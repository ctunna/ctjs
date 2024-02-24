#pragma once

#include "ctjs/runtime/value.h"

namespace ctjs {
class ReturnException : public std::exception {
 public:
  ReturnException(Value value) : value_(value) {}

  Value value() const { return value_; }

 private:
  Value value_;
};
}  // namespace ctjs
