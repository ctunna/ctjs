#pragma once

#include <memory>

#include "ctjs/ast/ast.h"
#include "ctjs/util/box.h"

namespace ctjs {
class PrintVisitor {
 public:
  PrintVisitor(int indent = 0) : indent_(indent) {}

  void operator()(util::Box<ast::Program>& program) const;

  void operator()(util::Box<ast::BlockStatement>& statement) const;
  void operator()(util::Box<ast::ReturnStatement>& statement) const;
  void operator()(util::Box<ast::IfStatement>& statement) const;
  void operator()(util::Box<ast::WhileStatement>& statement) const;
  void operator()(util::Box<ast::ForInStatement>& statement) const;
  void operator()(util::Box<ast::ExpressionStatement>& statement) const;
  void operator()(util::Box<ast::VariableDeclaration>& decl) const;
  void operator()(util::Box<ast::VariableDeclarator>& decl) const;
  void operator()(util::Box<ast::FunctionDeclaration>& decl) const;

  void operator()(util::Box<ast::ArrayExpression>& expression) const;
  void operator()(util::Box<ast::AssignmentExpression>& expression) const;
  void operator()(util::Box<ast::BinaryExpression>& expression) const;
  void operator()(util::Box<ast::CallExpression>& expression) const;
  void operator()(util::Box<ast::Identifier>& id) const;
  void operator()(util::Box<ast::Literal>& literal) const;
  void operator()(util::Box<ast::MemberExpression>& expression) const;
  void operator()(util::Box<ast::ObjectExpression>& expression) const;
  void operator()(util::Box<ast::FunctionExpression>& expression) const;

 private:
  int indent_{};
};

}  // namespace ctjs