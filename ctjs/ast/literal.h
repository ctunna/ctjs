#pragma once

#include <string>

#include "../value.h"
#include "expression.h"
#include "source_location.h"

namespace ctjs::ast {
class Literal : public Expression {
 public:
  Literal(std::string file_name, SourceLocation loc, Value value);

  void to_string(int indent = 0) override;
  auto evaluate([[maybe_unused]] std::shared_ptr<Environment> environment)
      -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  Value value_;
};
}  // namespace ctjs::ast
