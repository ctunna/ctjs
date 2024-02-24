#pragma once

#include <string>
#include <vector>

#include "ctjs/ast/variable_declarator.h"

namespace ctjs::ast {
class VariableDeclaration {
 public:
  VariableDeclaration(std::string file_name, SourceLocation loc,
                      std::vector<VariableDeclaratorPtr> declarations);

  std::string const file_name;
  SourceLocation const loc;
  std::string const kind{"var"};
  std::vector<VariableDeclaratorPtr> declarations;
};
}  // namespace ctjs::ast
