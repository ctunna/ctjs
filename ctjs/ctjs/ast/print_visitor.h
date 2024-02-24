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

namespace ctjs::ast {
class PrintVisitor {
 public:
  PrintVisitor(int indent = 0) : indent_(indent) {}

  void operator()(std::shared_ptr<Program> program) const;

  void operator()(std::shared_ptr<BlockStatement> statement) const;
  void operator()(std::shared_ptr<ReturnStatement> statement) const;
  void operator()(std::shared_ptr<IfStatement> statement) const;
  void operator()(std::shared_ptr<WhileStatement> statement) const;
  void operator()(std::shared_ptr<ExpressionStatement> statement) const;
  void operator()(std::shared_ptr<VariableDeclaration> decl) const;
  void operator()(std::shared_ptr<VariableDeclarator> decl) const;
  void operator()(std::shared_ptr<FunctionDeclaration> decl) const;

  void operator()(std::shared_ptr<ArrayExpression> expression) const;
  void operator()(std::shared_ptr<AssignmentExpression> expression) const;
  void operator()(std::shared_ptr<BinaryExpression> expression) const;
  void operator()(std::shared_ptr<CallExpression> expression) const;
  void operator()(std::shared_ptr<Identifier> id) const;
  void operator()(std::shared_ptr<Literal> literal) const;

 private:
  int indent_{};
};

}  // namespace ctjs::ast