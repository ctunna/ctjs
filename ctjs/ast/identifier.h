#pragma once

#include "expression.h"
#include "source_location.h"
namespace ctjs::ast {
class Identifier : public Expression {
 public:
  Identifier(std::string file_name, SourceLocation loc, std::string name);

  void to_string(int indent = 0) override;
  auto evaluate(Environment& environment) -> Value override;
  auto name() const -> std::string;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::string const name_;
};
}  // namespace ctjs::ast
