#include "ctjs/ast/binary_expression.h"

#include <iostream>

namespace ctjs::ast {
std::string to_symbol(BinaryOperator op) {
  switch (op) {
    case BinaryOperator::Add:
      return "+";
    case BinaryOperator::Sub:
      return "-";
    case BinaryOperator::Mul:
      return "*";
    case BinaryOperator::Div:
      return "/";
    case BinaryOperator::Mod:
      return "%";
    case BinaryOperator::Pow:
      return "**";
    case BinaryOperator::Equal:
      return "==";
    case BinaryOperator::NotEqual:
      return "!=";
    case BinaryOperator::LessThan:
      return "<";
    case BinaryOperator::LessThanOrEqual:
      return "<=";
    case BinaryOperator::GreaterThan:
      return ">";
    case BinaryOperator::GreaterThanOrEqual:
      return ">=";
    case BinaryOperator::And:
      return "&&";
    case BinaryOperator::Or:
      return "||";
    case BinaryOperator::BitwiseAnd:
      return "&";
    case BinaryOperator::BitwiseOr:
      return "|";
    case BinaryOperator::BitwiseXor:
      return "^";
    case BinaryOperator::LeftShift:
      return "<<";
    case BinaryOperator::RightShift:
      return ">>";
    case BinaryOperator::UnsignedRightShift:
      return ">>>";
    case BinaryOperator::InstanceOf:
      return "instanceof";
    case BinaryOperator::In:
      return "in";
    default:
      throw std::runtime_error("Unknown BinaryOperator");
  }
}

BinaryExpression::BinaryExpression(std::string file_name, SourceLocation loc,
                                   BinaryOperator op,
                                   std::shared_ptr<Expression> left,
                                   std::shared_ptr<Expression> right)
    : file_name_(file_name), loc_(loc), op_(op), left_(left), right_(right) {}

void BinaryExpression::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "BinaryExpression(" << to_symbol(op_)
            << ",\n";
  left_->to_string(indent + 2);
  std::cout << ",\n";
  right_->to_string(indent + 2);
  std::cout << "\n" << std::string(indent, ' ') << ")";
}

auto BinaryExpression::evaluate(std::shared_ptr<Environment> environment)
    -> Value {
  auto left{left_->evaluate(environment)};
  auto right{right_->evaluate(environment)};
  switch (op_) {
    case BinaryOperator::Add:
      return left + right;
    case BinaryOperator::Sub:
      return left - right;
    case BinaryOperator::Mul:
      return left * right;
    case BinaryOperator::Equal:
      return left == right;
    case BinaryOperator::GreaterThan:
      return left > right;
    case BinaryOperator::LessThan:
      return left < right;
    default:
      throw std::runtime_error("Unknown BinaryOperator");
  }
}
}  // namespace ctjs::ast
