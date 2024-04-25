#include "ctjs/visitor/interpreter_visitor.h"

#include <memory>
#include <variant>

#include "ctjs/runtime/array.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/return_exception.h"
#include "ctjs/runtime/user_defined_function.h"

namespace ctjs {
InterpreterVisitor::InterpreterVisitor(std::shared_ptr<Environment> environment)
    : environment_(std::move(environment)) {}

auto InterpreterVisitor::operator()(util::Box<ast::Program>& program) -> Value {
  for (auto& stmt : program->body) {
    std::visit(*this, stmt);
  }
  return {};
}

auto InterpreterVisitor::operator()(util::Box<ast::BlockStatement>& statement)
    -> Value {
  auto environment{std::make_shared<Environment>(environment_)};
  for (auto& stmt : statement->body) {
    std::visit(InterpreterVisitor{environment}, stmt);
  }
  return {};
}

auto InterpreterVisitor::operator()(util::Box<ast::ReturnStatement>& statement)
    -> Value {
  auto value{statement->argument_ ? std::visit(*this, *statement->argument_)
                                  : Value()};
  throw ReturnException(value);
}

auto InterpreterVisitor::operator()(util::Box<ast::VariableDeclaration>& decl)
    -> Value {
  for (auto& decl : decl->declarations) {
    std::visit(*this, decl);
  }
  return {};
}

auto InterpreterVisitor::operator()(util::Box<ast::VariableDeclarator>& decl)
    -> Value {
  auto value{std::visit(*this, decl->init)};
  auto id{std::get<util::Box<ast::Identifier>>(decl->id)};
  environment_->define(id->name, value);
  return value;
}

auto InterpreterVisitor::operator()(util::Box<ast::IfStatement>& statement)
    -> Value {
  auto test{std::visit(*this, statement->test)};
  if (static_cast<bool>(test)) {
    return std::visit(*this, statement->consquent);
  }
  if (statement->alternate) {
    return std::visit(*this, *statement->alternate);
  }
  return {};
}

auto InterpreterVisitor::operator()(util::Box<ast::WhileStatement>& statement)
    -> Value {
  while (static_cast<bool>(std::visit(*this, statement->condition))) {
    std::visit(*this, statement->body);
  }
  return {};
}

auto InterpreterVisitor::operator()(util::Box<ast::ForInStatement>& statement)
    -> Value {
  auto value{std::visit(*this, statement->right)};
  auto obj{value.get<std::shared_ptr<Object>>()};
  auto environment{std::make_shared<Environment>(environment_)};
  for (auto const& [key, value] : obj->properties()) {
    auto id{std::get<util::Box<ast::Identifier>>(statement->left)};
    environment->define(id->name, Value(key));
    std::visit(InterpreterVisitor{environment}, statement->body);
  }
  return {};
}

auto InterpreterVisitor::operator()(util::Box<ast::FunctionDeclaration>& decl)
    -> Value {
  std::shared_ptr<Object> function{std::make_shared<UserDefinedFunction>(
      &decl->params, &decl->body, environment_)};
  Value value(function);
  auto id{std::get<util::Box<ast::Identifier>>(decl->id)};
  environment_->define(id->name, value);
  return value;
}

auto InterpreterVisitor::operator()(
    util::Box<ast::ExpressionStatement>& statement) -> Value {
  return std::visit(*this, statement->expression_);
}

auto InterpreterVisitor::operator()(util::Box<ast::ArrayExpression>& expression)
    -> Value {
  auto array{std::make_shared<Array>()};
  for (auto& element : expression->elements) {
    array->push(std::visit(*this, element));
  }
  return Value(array);
}

auto InterpreterVisitor::operator()(
    util::Box<ast::AssignmentExpression>& expression) -> Value {
  auto value{std::visit(*this, expression->right)};
  auto id{std::get<util::Box<ast::Identifier>>(expression->left)};
  environment_->set(id->name, value);
  return value;
}

auto InterpreterVisitor::operator()(
    util::Box<ast::BinaryExpression>& expression) -> Value {
  auto left{std::visit(*this, expression->left)};
  auto right{std::visit(*this, expression->right)};
  switch (expression->op) {
    case ast::BinaryOperator::Add:
      return left + right;
    case ast::BinaryOperator::Sub:
      return left - right;
    case ast::BinaryOperator::Mul:
      return left * right;
    case ast::BinaryOperator::Equal:
      return Value(left == right);
    case ast::BinaryOperator::GreaterThan:
      return Value(left > right);
    case ast::BinaryOperator::LessThan:
      return Value(left < right);
    default:
      throw std::runtime_error("Unknown BinaryOperator");
  }
}

auto InterpreterVisitor::operator()(util::Box<ast::CallExpression>& expression)
    -> Value {
  auto val{std::visit(*this, expression->callee)};
  auto obj{val.get<std::shared_ptr<Object>>()};
  auto callee{std::dynamic_pointer_cast<Function>(obj)};
  std::vector<Value> args;
  for (auto& arg : expression->arguments) {
    args.push_back(std::visit(*this, arg));
  }
  try {
    return callee->call(args);
  } catch (ReturnException& e) {
    return e.value();
  }
}

auto InterpreterVisitor::operator()(util::Box<ast::Identifier>& id) -> Value {
  return environment_->get(id->name);
}

auto InterpreterVisitor::operator()(util::Box<ast::Literal>& literal) -> Value {
  return literal->value;
}

auto InterpreterVisitor::operator()(
    util::Box<ast::MemberExpression>& expression) -> Value {
  auto object{std::visit(*this, expression->object)};
  auto property{std::visit(*this, expression->property)};
  return object[property];
}

auto InterpreterVisitor::operator()(
    util::Box<ast::ObjectExpression>& expression) -> Value {
  auto object{std::make_shared<Object>()};
  for (auto& prop : expression->properties) {
    auto key{std::get<util::Box<ast::Identifier>>(prop.key)};
    auto value{std::visit(*this, prop.value)};
    object->set_property(key->name, value);
  }
  return Value(object);
}

auto InterpreterVisitor::operator()(
    util::Box<ast::FunctionExpression>& expression) -> Value {
  std::shared_ptr<Object> function{std::make_shared<UserDefinedFunction>(
      &expression->params, &expression->body, environment_)};
  return Value(function);
}

}  // namespace ctjs
