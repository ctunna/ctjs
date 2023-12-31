#pragma once

#include <string>

#include "expression.h"
#include "pattern.h"

namespace ast {
class Literal : public Pattern, public Expression {
public:
  std::string name;
};

} // namespace ast

