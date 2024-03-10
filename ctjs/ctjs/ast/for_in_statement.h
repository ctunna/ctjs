#pragma once

#include <string>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/identifier.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"

namespace ctjs::ast {
class ForInStatement {
 public:
  ForInStatement(std::string file_name, SourceLocation loc, IdentifierPtr left,
                 ExpressionPtr right, StatementPtr body);

  std::string const file_name;
  SourceLocation const loc;
  IdentifierPtr const left;
  ExpressionPtr const right;
  StatementPtr const body;
};
}  // namespace ctjs::ast
