#pragma once

#include <string>
#include <vector>

#include "declaration.h"
#include "variable_declarator.h"

namespace ast {
class VariableDeclaration : public Declaration {
private:
  const std::string kind = "var";
  std::vector<VariableDeclarator> declarations;
};
} // namespace ast

