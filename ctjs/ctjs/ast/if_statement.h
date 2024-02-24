#pragma once

#include <optional>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"

namespace ctjs::ast {
class IfStatement {
 public:
  IfStatement(std::string file_name, SourceLocation loc, ExpressionPtr test,
              StatementPtr consequent, std::optional<StatementPtr> alternate);

  std::string const file_name;
  SourceLocation const loc;
  ExpressionPtr const test;
  StatementPtr const consquent;
  std::optional<StatementPtr> const alternate;
};
}  // namespace ctjs::ast
