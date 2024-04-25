#pragma once

#include <vector>

#include "ctjs/runtime/object.h"

namespace ctjs {

class Value;

class Function : public Object {
 public:
  virtual auto call(std::vector<Value> args) -> Value = 0;
};

}  // namespace ctjs
