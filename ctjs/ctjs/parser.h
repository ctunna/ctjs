#pragma once

#include <memory>
#include <optional>
#include <string_view>

#include "ctjs/ast/ast.h"
#include "ctjs/token.h"
#include "ctjs/tokenizer.h"
#include "ctjs/util/box.h"

namespace ctjs {
class Parser {
 public:
  Parser(std::string_view source);
  Parser(const Parser &) = delete;
  Parser(Parser &&) = delete;
  Parser &operator=(const Parser &) = delete;
  Parser &operator=(Parser &&) = delete;

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
  auto optional_parse_identifier() -> std::optional<util::Box<ast::Identifier>>;
  auto parse_identifier() -> util::Box<ast::Identifier>;
  auto optional_parse_numeric_literal()
      -> std::optional<util::Box<ast::Literal>>;
  auto parse_numeric_literal() -> util::Box<ast::Literal>;
  auto optional_parse_string_literal()
      -> std::optional<util::Box<ast::Literal>>;
  auto parse_string_literal() -> util::Box<ast::Literal>;
  auto optional_parse_array_expression()
      -> std::optional<util::Box<ast::ArrayExpression>>;
  auto parse_array_expression() -> util::Box<ast::ArrayExpression>;
  auto optional_parse_object_expression()
      -> std::optional<util::Box<ast::ObjectExpression>>;
  auto parse_object_expression() -> util::Box<ast::ObjectExpression>;
  auto parse_expression() -> ast::Expression;
  auto consume_token(ast::TokenType type) -> Token;
  auto expect_token(ast::TokenType type) -> std::optional<Token>;

  std::string file_name_{"index.js"};
  ast::SourceLocation location_{"index.js", ast::Position(0, 0),
                                ast::Position(0, 0)};
  Tokenizer tokenizer_;
};
}  // namespace ctjs
