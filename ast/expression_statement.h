#pragma once

#include "expression.h"
#include "statement.h"

namespace ast {
class ExpressionStatement : public Statement {
private:
  Expression expression;
};
}


