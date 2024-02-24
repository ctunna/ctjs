#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"

namespace ctjs::ast {

// using Expression =
//     std::variant<ArrayExpression, AssignmentExpression, BinaryExpression,
//                  CallExpression, Identifier, Literal>;
class CallExpression {
 public:
  CallExpression(std::string file_name, SourceLocation loc,
                 ExpressionPtr callee, std::vector<ExpressionPtr> arguments);

  std::string const file_name;
  SourceLocation const loc;
  ExpressionPtr const callee;
  std::vector<ExpressionPtr> const arguments;
};
}  // namespace ctjs::ast
