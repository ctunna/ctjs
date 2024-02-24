#pragma once

#include <memory>
#include <optional>
#include <string_view>

#include "ctjs/ast/block_statement.h"
#include "ctjs/ast/expression_statement.h"
#include "ctjs/ast/function_declaration.h"
#include "ctjs/ast/identifier.h"
#include "ctjs/ast/if_statement.h"
#include "ctjs/ast/literal.h"
#include "ctjs/ast/position.h"
#include "ctjs/ast/program.h"
#include "ctjs/ast/return_statement.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"
#include "ctjs/ast/variable_declaration.h"
#include "ctjs/ast/while_statement.h"
#include "ctjs/token.h"
#include "ctjs/tokenizer.h"

namespace ctjs {
class Parser {
 public:
  Parser(std::string_view source);
  Parser(const Parser &) = delete;
  Parser(Parser &&) = delete;
  Parser &operator=(const Parser &) = delete;
  Parser &operator=(Parser &&) = delete;

  auto parse() -> std::shared_ptr<ast::Program>;

 private:
  auto parse_statement() -> ast::StatementPtr;

  auto parse_return_statement() -> std::shared_ptr<ast::ReturnStatement>;

  auto parse_variable_declaration()
      -> std::shared_ptr<ast::VariableDeclaration>;

  auto parse_function_declaration()
      -> std::shared_ptr<ast::FunctionDeclaration>;

  auto parse_block_statement() -> std::shared_ptr<ast::BlockStatement>;

  auto parse_if_statement() -> std::shared_ptr<ast::IfStatement>;

  auto parse_while_statement() -> std::shared_ptr<ast::WhileStatement>;

  auto parse_expression_statement()
      -> std::shared_ptr<ast::ExpressionStatement>;

  auto optional_parse_identifier()
      -> std::optional<std::shared_ptr<ast::Identifier>>;

  auto parse_identifier() -> std::shared_ptr<ast::Identifier>;

  auto optional_parse_numeric_literal()
      -> std::optional<std::shared_ptr<ast::Literal>>;

  auto parse_numeric_literal() -> std::shared_ptr<ast::Literal>;

  auto optional_parse_string_literal()
      -> std::optional<std::shared_ptr<ast::Literal>>;

  auto parse_string_literal() -> std::shared_ptr<ast::Literal>;

  auto parse_expression() -> ast::ExpressionPtr;

  auto consume_token(ast::TokenType type) -> Token;

  auto expect_token(ast::TokenType type) -> std::optional<Token>;

  std::string file_name{"index.js"};
  ast::SourceLocation location_{"index.js", ast::Position(0, 0),
                                ast::Position(0, 0)};
  Tokenizer tokenizer_;
};
}  // namespace ctjs
