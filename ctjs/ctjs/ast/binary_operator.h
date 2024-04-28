#pragma once

#include <stdexcept>
#include <string>

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

inline auto to_symbol(BinaryOperator oper) -> std::string {
  switch (oper) {
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
}  // namespace ctjs::ast