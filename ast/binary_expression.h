#pragma once

#include "expression.h"

namespace ast {

enum class BinaryOperator {
  Add,
  Sub,
  Mul,
  Div,
  Mod,
  Pow,
  Equal,
  NotEqual,
  LessThan,
  LessThanOrEqual,
  GreaterThan,
  GreaterThanOrEqual,
  And,
  Or,
  BitwiseAnd,
  BitwiseOr,
  BitwiseXor,
  LeftShift,
  RightShift,
  UnsignedRightShift,
  InstanceOf,
  In,
};

class BinaryExpression : public Expression {
private:
  BinaryOperator op;
  Expression left;
  Expression right;
};

} // namespace ast

