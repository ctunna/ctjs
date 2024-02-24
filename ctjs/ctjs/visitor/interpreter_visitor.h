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
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"

namespace ctjs {
class InterpreterVisitor {
 public:
  auto operator()(std::shared_ptr<ast::Program> program,
                  std::shared_ptr<Environment> environment) const -> Value;

  auto operator()(std::shared_ptr<ast::BlockStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::ReturnStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::IfStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::WhileStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::ExpressionStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::VariableDeclaration> decl,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::VariableDeclarator> decl,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::FunctionDeclaration> decl,
                  std::shared_ptr<Environment> environment) const -> Value;

  auto operator()(std::shared_ptr<ast::ArrayExpression> expression,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::AssignmentExpression> expression,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::BinaryExpression> expression,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::CallExpression> expression,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::Identifier> id,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ast::Literal> literal,
                  std::shared_ptr<Environment> environment) const -> Value;
};

}  // namespace ctjs