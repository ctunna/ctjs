#pragma once

#include <string>

#include "pattern.h"
#include "expression.h"

namespace ast {
class VariableDeclarator {
private:
  Pattern id;
  Expression init;
};
} // namespace ast

