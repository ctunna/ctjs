#pragma once

#include <memory>
#include <optional>
#include <string_view>

#include "ast/binary_expression.h"
#include "ast/block_statement.h"
#include "ast/expression_statement.h"
#include "ast/identifier.h"
#include "ast/if_statement.h"
#include "ast/literal.h"
#include "ast/position.h"
#include "ast/program.h"
#include "ast/source_location.h"
#include "ast/statement.h"
#include "ast/variable_declaration.h"
#include "tokenizer.h"

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
  auto parse_statement() -> std::shared_ptr<ast::Statement>;

  auto parse_block_statement() -> std::shared_ptr<ast::BlockStatement>;

  auto parse_variable_declaration()
      -> std::shared_ptr<ast::VariableDeclaration>;

  auto parse_if_statement() -> std::shared_ptr<ast::IfStatement>;

  auto optional_parse_identifier()
      -> std::optional<std::shared_ptr<ast::Identifier>>;

  auto parse_identifier() -> std::shared_ptr<ast::Identifier>;

  auto optional_parse_numeric_literal()
      -> std::optional<std::shared_ptr<ast::Literal>>;

  auto parse_numeric_literal() -> std::shared_ptr<ast::Literal>;

  auto parse_expression() -> std::shared_ptr<ast::Expression>;

  void consume_semicolon();

  std::string file_name_{"index.js"};
  ast::SourceLocation location_{"index.js", ast::Position(0, 0),
                                ast::Position(0, 0)};
  Tokenizer tokenizer_;
};
}  // namespace ctjs
