#pragma once

#include <memory>

#include "ctjs/ast/binary_operator.h"
#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"

namespace ctjs::ast {

class BinaryExpression {
 public:
  BinaryExpression(std::string file_name, SourceLocation loc, BinaryOperator op,
                   ExpressionPtr left, ExpressionPtr right);

  std::string const file_name;
  SourceLocation const loc;
  BinaryOperator const op;
  ExpressionPtr const left;
  ExpressionPtr const right;
};
}  // namespace ctjs::ast
