#pragma once

#include <memory>
#include <string>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"

namespace ctjs::ast {
class AssignmentExpression {
 public:
  AssignmentExpression(std::string file_name, SourceLocation loc,
                       ExpressionPtr left, ExpressionPtr right);

  std::string const file_name;
  SourceLocation const loc;
  ExpressionPtr const left;
  ExpressionPtr const right;
};
}  // namespace ctjs::ast