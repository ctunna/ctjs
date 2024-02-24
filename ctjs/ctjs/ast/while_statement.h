#pragma once

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"

namespace ctjs::ast {
class WhileStatement {
 public:
  WhileStatement(std::string file_name, SourceLocation loc,
                 ExpressionPtr condition, StatementPtr body);

  std::string const file_name;
  SourceLocation const loc;
  ExpressionPtr const condition;
  StatementPtr const body;
};
}  // namespace ctjs::ast
