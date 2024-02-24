#pragma once

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"

namespace ctjs::ast {
class ExpressionStatement {
 public:
  ExpressionStatement(std::string file_name, SourceLocation loc,
                      ExpressionPtr expression);

  ExpressionPtr const expression_;
  std::string const file_name;
  SourceLocation const loc;
};
}  // namespace ctjs::ast
