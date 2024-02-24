#pragma once

#include <memory>
#include <variant>

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
using AstNode = std::variant<
    std::shared_ptr<Program>, std::shared_ptr<ArrayExpression>,
    std::shared_ptr<AssignmentExpression>, std::shared_ptr<BinaryExpression>,
    std::shared_ptr<BlockStatement>, std::shared_ptr<CallExpression>,
    std::shared_ptr<ExpressionStatement>, std::shared_ptr<FunctionDeclaration>,
    std::shared_ptr<Identifier>, std::shared_ptr<IfStatement>,
    std::shared_ptr<Literal>, std::shared_ptr<ReturnStatement>,
    std::shared_ptr<VariableDeclaration>, std::shared_ptr<WhileStatement>>;
}  // namespace ctjs::ast
