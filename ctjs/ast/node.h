#pragma once

#include <memory>

#include "../environment.h"
#include "../value.h"

namespace ctjs::ast {
class Node {
 public:
  virtual ~Node() = default;
  virtual void to_string(int indent = 0) = 0;
  virtual auto evaluate(std::shared_ptr<Environment> environment) -> Value = 0;
};
}  // namespace ctjs::ast