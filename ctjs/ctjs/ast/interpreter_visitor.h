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

namespace ctjs::ast {
class InterpreterVisitor {
 public:
  auto operator()(std::shared_ptr<Program> program,
                  std::shared_ptr<Environment> environment) const -> Value;

  auto operator()(std::shared_ptr<BlockStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ReturnStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<IfStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<WhileStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<ExpressionStatement> statement,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<VariableDeclaration> decl,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<VariableDeclarator> decl,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<FunctionDeclaration> decl,
                  std::shared_ptr<Environment> environment) const -> Value;

  auto operator()(std::shared_ptr<ArrayExpression> expression,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<AssignmentExpression> expression,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<BinaryExpression> expression,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<CallExpression> expression,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<Identifier> id,
                  std::shared_ptr<Environment> environment) const -> Value;
  auto operator()(std::shared_ptr<Literal> literal,
                  std::shared_ptr<Environment> environment) const -> Value;
};

}  // namespace ctjs::ast