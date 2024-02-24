#pragma once

#include <memory>
#include <string>
#include <variant>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/identifier.h"

namespace ctjs::ast {

class VariableDeclarator {
 public:
  VariableDeclarator(std::string file_name, SourceLocation loc,
                     IdentifierPtr id, ExpressionPtr init);

  std::string const file_name;
  SourceLocation const loc;
  IdentifierPtr const id;
  ExpressionPtr const init;
};

using VariableDeclaratorPtr = std::variant<std::shared_ptr<VariableDeclarator>>;

}  // namespace ctjs::ast
