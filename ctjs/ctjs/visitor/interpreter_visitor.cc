#include "ctjs/visitor/interpreter_visitor.h"

#include <iostream>
#include <variant>

#include "ctjs/runtime/return_exception.h"

namespace ctjs {
auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::Program> program,
    std::shared_ptr<Environment> environment) const -> Value {
  for (auto& stmt : program->body) {
    visit(stmt, environment);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::BlockStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  for (auto& stmt : statement->body) {
    visit(stmt, environment);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::ReturnStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  auto value{statement->argument_ ? visit(*statement->argument_, environment)
                                  : Value()};
  throw ReturnException(value);
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::VariableDeclaration> decl,
    std::shared_ptr<Environment> environment) const -> Value {
  for (auto& decl : decl->declarations) {
    visit(decl, environment);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::VariableDeclarator> decl,
    std::shared_ptr<Environment> environment) const -> Value {
  auto value{visit(decl->init, environment)};
  auto id{std::get<std::shared_ptr<ast::Identifier>>(decl->id)};
  environment->set(id->name, value);
  return value;
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::IfStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  auto test{visit(statement->test, environment)};
  if (static_cast<bool>(test)) {
    return visit(statement->consquent, environment);
  } else if (statement->alternate) {
    return visit(*statement->alternate, environment);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::WhileStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  while (static_cast<bool>(visit(statement->condition, environment))) {
    visit(statement->body, environment);
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::FunctionDeclaration> decl,
    std::shared_ptr<Environment> environment) const -> Value {
  Function function{decl, environment};
  auto id{std::get<std::shared_ptr<ast::Identifier>>(decl->id)};
  environment->set(id->name, function);
  return function;
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::ExpressionStatement> statement,
    std::shared_ptr<Environment> environment) const -> Value {
  return visit(statement->expression_, environment);
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::ArrayExpression> expression,
    std::shared_ptr<Environment> environment) const -> Value {
  std::vector<Value> values;
  for (auto const& element : expression->elements) {
    values.push_back(visit(element, environment));
  }
  return Value();
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::AssignmentExpression> expression,
    std::shared_ptr<Environment> environment) const -> Value {
  auto value{visit(expression->right, environment)};
  auto id{std::get<std::shared_ptr<ast::Identifier>>(expression->left)};
  environment->set(id->name, value);
  return value;
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::BinaryExpression> expression,
    std::shared_ptr<Environment> environment) const -> Value {
  auto left{visit(expression->left, environment)};
  auto right{visit(expression->right, environment)};
  switch (expression->op) {
    case ast::BinaryOperator::Add:
      return left + right;
    case ast::BinaryOperator::Sub:
      return left - right;
    case ast::BinaryOperator::Mul:
      return left * right;
    case ast::BinaryOperator::Equal:
      return left == right;
    case ast::BinaryOperator::GreaterThan:
      return left > right;
    case ast::BinaryOperator::LessThan:
      return left < right;
    default:
      throw std::runtime_error("Unknown BinaryOperator");
  }
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::CallExpression> expression,
    std::shared_ptr<Environment> environment) const -> Value {
  auto callee{visit(expression->callee, environment).get<Function>()};
  std::vector<Value> args;
  for (auto& arg : expression->arguments) {
    args.push_back(visit(arg, environment));
  }
  try {
    return callee.call(args);
  } catch (ReturnException& e) {
    return e.value();
  }
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::Identifier> id,
    std::shared_ptr<Environment> environment) const -> Value {
  return environment->get(id->name);
}

auto InterpreterVisitor::operator()(
    std::shared_ptr<ast::Literal> literal,
    [[maybe_unused]] std::shared_ptr<Environment> environment) const -> Value {
  return literal->value;
}

}  // namespace ctjs
