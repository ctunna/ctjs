#pragma once

#include <functional>

#include "ctjs/runtime/function.h"
#include "ctjs/runtime/value.h"

namespace ctjs {
class BuiltinFunction : public Function {
 public:
  explicit BuiltinFunction(std::function<Value(std::vector<Value>)> func)
      : func_(std::move(func)) {}

  auto call(std::vector<Value> args) -> Value override { return func_(args); }

 private:
  std::function<Value(std::vector<Value>)> func_;
};

}  // namespace ctjs
