#pragma once

#include <string>

#include "expression.h"
#include "source_location.h"

namespace ctjs::ast {
class Literal : public Expression {
 public:
  Literal(std::string file_name, SourceLocation loc, int value);

  void to_string(int indent = 0) override;
  auto evaluate([[maybe_unused]] Environment& environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  [[maybe_unused]] int value_;
};
}  // namespace ctjs::ast
