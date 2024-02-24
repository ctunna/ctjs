#pragma once

#include <memory>

#include "ctjs/ast/array_expression.h"
#include "ctjs/ast/assignment_expression.h"
#include "ctjs/ast/binary_expression.h"
#include "ctjs/ast/block_statement.h"
#include "ctjs/ast/call_expression.h"
#include "ctjs/ast/expression_statement.h"
#include "ctjs/ast/function_declaration.h"
#include "ctjs/ast/identifier.h"
#include "ctjs/ast/if_statement.h"
#include "ctjs/ast/literal.h"
#include "ctjs/ast/program.h"
#include "ctjs/ast/return_statement.h"
#include "ctjs/ast/variable_declaration.h"
#include "ctjs/ast/while_statement.h"

namespace ctjs {
class PrintVisitor {
 public:
  PrintVisitor(int indent = 0) : indent_(indent) {}

  void operator()(std::shared_ptr<ast::Program> program) const;

  void operator()(std::shared_ptr<ast::BlockStatement> statement) const;
  void operator()(std::shared_ptr<ast::ReturnStatement> statement) const;
  void operator()(std::shared_ptr<ast::IfStatement> statement) const;
  void operator()(std::shared_ptr<ast::WhileStatement> statement) const;
  void operator()(std::shared_ptr<ast::ExpressionStatement> statement) const;
  void operator()(std::shared_ptr<ast::VariableDeclaration> decl) const;
  void operator()(std::shared_ptr<ast::VariableDeclarator> decl) const;
  void operator()(std::shared_ptr<ast::FunctionDeclaration> decl) const;

  void operator()(std::shared_ptr<ast::ArrayExpression> expression) const;
  void operator()(std::shared_ptr<ast::AssignmentExpression> expression) const;
  void operator()(std::shared_ptr<ast::BinaryExpression> expression) const;
  void operator()(std::shared_ptr<ast::CallExpression> expression) const;
  void operator()(std::shared_ptr<ast::Identifier> id) const;
  void operator()(std::shared_ptr<ast::Literal> literal) const;

 private:
  int indent_{};
};

}  // namespace ctjs