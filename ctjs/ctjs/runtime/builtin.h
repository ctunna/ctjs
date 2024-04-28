#pragma once

#include <functional>
#include <memory>

#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/function.h"
#include "ctjs/runtime/value.h"

namespace ctjs {

class Builtin {
 public:
  static void apply(const std::shared_ptr<Environment>& environment);

  class Function : public ctjs::Function {
   public:
    explicit Function(std::function<Value(std::vector<Value>)> func);

    auto call(std::vector<Value> args) -> Value override;

   private:
    std::function<Value(std::vector<Value>)> func_;
  };
};
}  // namespace ctjs