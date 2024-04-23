#pragma once

#include <optional>
#include <string_view>

#include "ctjs/ast/ast.h"
#include "ctjs/ast/position.h"
#include "ctjs/token.h"
#include "ctjs/tokenizer.h"
#include "ctjs/util/box.h"

namespace ctjs {
class Parser {
 public:
  Parser(std::string file_name, std::string_view source);
  Parser(const Parser &) = delete;
  Parser(Parser &&) = delete;
  auto operator=(const Parser &) -> Parser & = delete;
  auto operator=(Parser &&) -> Parser & = delete;

  auto parse() -> util::Box<ast::Program>;

 private:
  auto parse_statement() -> ast::Statement;
  auto parse_return_statement() -> util::Box<ast::ReturnStatement>;
  auto parse_variable_declaration() -> util::Box<ast::VariableDeclaration>;
  auto parse_function_declaration() -> util::Box<ast::FunctionDeclaration>;
  auto parse_block_statement() -> util::Box<ast::BlockStatement>;
  auto parse_if_statement() -> util::Box<ast::IfStatement>;
  auto parse_while_statement() -> util::Box<ast::WhileStatement>;
  auto parse_for_in_statement() -> util::Box<ast::ForInStatement>;
  auto parse_expression_statement() -> util::Box<ast::ExpressionStatement>;
  auto parse_identifier() -> util::Box<ast::Identifier>;
  auto parse_numeric_literal() -> util::Box<ast::Literal>;
  auto parse_bool_literal() -> util::Box<ast::Literal>;
  auto parse_string_literal() -> util::Box<ast::Literal>;
  auto parse_array_expression() -> util::Box<ast::ArrayExpression>;
  auto parse_object_expression() -> util::Box<ast::ObjectExpression>;
  auto parse_function_expression() -> util::Box<ast::FunctionExpression>;
  auto parse_secondary_expression(ast::Expression lhs) -> ast::Expression;
  auto parse_primary_expression() -> ast::Expression;
  auto parse_expression() -> ast::Expression;
  auto consume_token(ast::TokenType type) -> Token;
  auto expect_token(ast::TokenType type) -> std::optional<Token>;
  auto position() -> ast::Position;
  auto match_secondary_expression() -> bool;

  std::string file_name_{};
  Tokenizer tokenizer_;
};
}  // namespace ctjs
