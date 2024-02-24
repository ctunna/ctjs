#pragma once

#include "ctjs/ast/block_statement.h"
#include "ctjs/ast/expression.h"
#include "ctjs/ast/identifier.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"

namespace ctjs::ast {
class FunctionDeclaration {
 public:
  FunctionDeclaration(std::string file_name, SourceLocation loc,
                      IdentifierPtr id, std::vector<IdentifierPtr> params,
                      StatementPtr body);

  std::string const file_name;
  SourceLocation const loc;
  IdentifierPtr const id;
  std::vector<IdentifierPtr> const params;
  StatementPtr const body;
};
}  // namespace ctjs::ast
