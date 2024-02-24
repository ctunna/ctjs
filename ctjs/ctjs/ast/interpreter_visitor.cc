#include "ctjs/ast/interpreter_visitor.h"

#include <iostream>
#include <variant>

#include "ctjs/ast/return_exception.h"

namespace ctjs::ast {
auto InterpreterVisitor::operator()(
    std::shared_ptr<Program> program,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  for (auto& stmt : program->body) {
    std::visit(*this, stmt, e);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<BlockStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  for (auto& stmt : statement->body) {
    std::visit(*this, stmt, e);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ReturnStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  auto value{statement->argument_ ? std::visit(*this, *statement->argument_, e)
                                  : Value()};
  throw ReturnException(value);
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<VariableDeclaration> decl,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  for (auto& decl : decl->declarations) {
    std::visit(*this, decl, e);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<VariableDeclarator> decl,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  auto value{std::visit(*this, decl->init, e)};
  auto id{std::get<std::shared_ptr<Identifier>>(decl->id)};
  environment->set(id->name, value);
  return value;
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<IfStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  auto test{std::visit(*this, statement->test, e)};
  if (test.coerce<bool>()) {
    return std::visit(*this, statement->consquent, e);
  } else if (statement->alternate) {
    return std::visit(*this, *statement->alternate, e);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<WhileStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  while (std::visit(*this, statement->condition, e).coerce<bool>()) {
    std::visit(*this, statement->body, e);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<FunctionDeclaration> decl,
    std::shared_ptr<Environment> environment) const -> Value {
  Function function{decl, environment};
  auto id{std::get<std::shared_ptr<Identifier>>(decl->id)};
  environment->set(id->name, function);
  return function;
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ExpressionStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  return std::visit(*this, statement->expression_, e);
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ArrayExpression> expression,
    std::shared_ptr<Environment> environment) const -> Value {
  std::vector<Value> values;
  EnvironmentPtr e{environment};
  for (auto const& element : expression->elements) {
    values.push_back(std::visit(*this, element, e));
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<AssignmentExpression> expression,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  auto value{std::visit(*this, expression->right, e)};
  auto id{std::get<std::shared_ptr<Identifier>>(expression->left)};
  environment->set(id->name, value);
  return value;
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<BinaryExpression> expression,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  auto left{std::visit(*this, expression->left, e)};
  auto right{std::visit(*this, expression->right, e)};
  switch (expression->op) {
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

auto InterpreterVisitor::operator()(
    std::shared_ptr<CallExpression> expression,
    std::shared_ptr<Environment> environment) const -> Value {
  EnvironmentPtr e{environment};
  auto callee{std::visit(*this, expression->callee, e).coerce<Function>()};
  std::vector<Value> args;
  for (auto& arg : expression->arguments) {
    args.push_back(std::visit(*this, arg, e));
  }
  try {
    return callee.call(args);
  } catch (ReturnException& e) {
    return e.value();
  }
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<Identifier> id,
    std::shared_ptr<Environment> environment) const -> Value {
  return environment->get(id->name);
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<Literal> literal,
    [[maybe_unused]] std::shared_ptr<Environment> environment) const -> Value {
  return literal->value;
}

}  // namespace ctjs::ast