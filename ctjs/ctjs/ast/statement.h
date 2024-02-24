#pragma once

#include <memory>
#include <variant>

// #include "ctjs/ast/block_statement.h"
// #include "ctjs/ast/expression_statement.h"
// #include "ctjs/ast/function_declaration.h"
// #include "ctjs/ast/if_statement.h"
// #include "ctjs/ast/return_statement.h"
// #include "ctjs/ast/variable_declaration.h"
// #include "ctjs/ast/while_statement.h"

namespace ctjs::ast {
class BlockStatement;
class ExpressionStatement;
class FunctionDeclaration;
class IfStatement;
class ReturnStatement;
class VariableDeclaration;
class WhileStatement;

using StatementPtr = std::variant<
    std::shared_ptr<BlockStatement>, std::shared_ptr<ExpressionStatement>,
    std::shared_ptr<IfStatement>, std::shared_ptr<ReturnStatement>,
    std::shared_ptr<VariableDeclaration>, std::shared_ptr<FunctionDeclaration>,
    std::shared_ptr<WhileStatement>>;
}  // namespace ctjs::ast
