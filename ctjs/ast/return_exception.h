#pragma once

#include "../value.h"

namespace ctjs::ast {
class ReturnException : public std::exception {
 public:
  ReturnException(Value value) : value_(value) {}

  Value value() const { return value_; }

 private:
  Value value_;
};
}  // namespace ctjs::ast
