#pragma once

#include "ctjs/ast/ast.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"
#include "ctjs/util/box.h"

namespace ctjs {
class InterpreterVisitor {
 public:
  explicit InterpreterVisitor(Environment* environment);

  auto operator()(util::Box<ast::Program>& program) -> Value;

  auto operator()(util::Box<ast::BlockStatement>& statement) -> Value;
  auto operator()(util::Box<ast::ReturnStatement>& statement) -> Value;
  auto operator()(util::Box<ast::IfStatement>& statement) -> Value;
  auto operator()(util::Box<ast::WhileStatement>& statement) -> Value;
  auto operator()(util::Box<ast::ForInStatement>& statement) -> Value;
  auto operator()(util::Box<ast::ExpressionStatement>& statement) -> Value;
  auto operator()(util::Box<ast::VariableDeclaration>& decl) -> Value;
  auto operator()(util::Box<ast::VariableDeclarator>& decl) -> Value;
  auto operator()(util::Box<ast::FunctionDeclaration>& decl) -> Value;

  auto operator()(util::Box<ast::ArrayExpression>& expression) -> Value;
  auto operator()(util::Box<ast::AssignmentExpression>& expression) -> Value;
  auto operator()(util::Box<ast::BinaryExpression>& expression) -> Value;
  auto operator()(util::Box<ast::CallExpression>& expression) -> Value;
  auto operator()(util::Box<ast::Identifier>& id) -> Value;
  auto operator()(util::Box<ast::Literal>& literal) -> Value;
  auto operator()(util::Box<ast::MemberExpression>& expression) -> Value;
  auto operator()(util::Box<ast::ObjectExpression>& expression) -> Value;
  auto operator()(util::Box<ast::FunctionExpression>& expression) -> Value;

 private:
  Environment* environment_;
};

}  // namespace ctjs
