#pragma once

#include <memory>

#include "expression.h"
#include "source_location.h"

namespace ctjs::ast {
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
 public:
  BinaryExpression(std::string file_name, SourceLocation loc, BinaryOperator op,
                   std::shared_ptr<Expression> left,
                   std::shared_ptr<Expression> right);

  void to_string(int indent = 0) override;
  auto evaluate(Environment& environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  BinaryOperator op_;
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;
};

}  // namespace ctjs::ast
