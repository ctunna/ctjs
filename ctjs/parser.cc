#include "parser.h"

#include <iostream>

using ctjs::ast::BinaryOperator;

namespace ctjs {

ast::BinaryOperator to_binary_operator(TokenType type) {
  switch (type) {
    case TokenType::Plus:
      return BinaryOperator::Add;
    case TokenType::Minus:
      return BinaryOperator::Sub;
    case TokenType::Asterisk:
      return BinaryOperator::Mul;
    case TokenType::Slash:
      return BinaryOperator::Div;
    case TokenType::EqualsEquals:
      return BinaryOperator::Equal;
    case TokenType::LessThan:
      return BinaryOperator::LessThan;
    case TokenType::LessThanEquals:
      return BinaryOperator::LessThanOrEqual;
    case TokenType::GreaterThan:
      return BinaryOperator::GreaterThan;
    case TokenType::GreaterThanEquals:
      return BinaryOperator::GreaterThanOrEqual;
    default:
      throw std::runtime_error("Unknown binary operator");
  }
}

bool is_binary_operator(TokenType type) {
  switch (type) {
    case TokenType::Plus:
    case TokenType::Minus:
    case TokenType::Asterisk:
    case TokenType::Slash:
    case TokenType::EqualsEquals:
    case TokenType::LessThan:
    case TokenType::LessThanEquals:
    case TokenType::GreaterThan:
    case TokenType::GreaterThanEquals:
      return true;
    default:
      return false;
  }
}

Parser::Parser(std::string_view source) : tokenizer_(source) {}

auto Parser::parse() -> std::shared_ptr<ast::Program> {
  std::vector<std::shared_ptr<ast::Statement>> statements;
  while (tokenizer_.ready()) {
    statements.push_back(parse_statement());
  }
  return std::make_shared<ast::Program>(file_name_, location_, statements);
}

auto Parser::parse_statement() -> std::shared_ptr<ast::Statement> {
  auto token{tokenizer_.peek()};
  switch (token.type) {
    case TokenType::Var:
      return parse_variable_declaration();
    case TokenType::If:
      return parse_if_statement();
    default:
      throw std::runtime_error("Unknown statement");
  }
}

auto Parser::parse_block_statement() -> std::shared_ptr<ast::BlockStatement> {
  auto token{tokenizer_.next()};
  if (token.type != TokenType::CurlyOpen) {
    throw std::runtime_error("Expected {");
  }
  std::vector<std::shared_ptr<ast::Statement>> statements;
  while (tokenizer_.peek().type != TokenType::CurlyClose) {
    statements.push_back(parse_statement());
  }
  if (tokenizer_.next().type != TokenType::CurlyClose) {
    throw std::runtime_error("Expected }");
  }
  return std::make_shared<ast::BlockStatement>(file_name_, location_,
                                               statements);
}

auto Parser::parse_if_statement() -> std::shared_ptr<ast::IfStatement> {
  auto token{tokenizer_.next()};
  if (token.type != TokenType::If) {
    throw std::runtime_error("Expected if");
  }
  if (tokenizer_.next().type != TokenType::ParenOpen) {
    throw std::runtime_error("Expected (");
  }
  auto test{parse_expression()};
  std::cout << tokenizer_.peek().value << std::endl;
  if (tokenizer_.next().type != TokenType::ParenClose) {
    throw std::runtime_error("Expected )");
  }
  auto consequent{tokenizer_.peek().type == TokenType::CurlyOpen
                      ? parse_block_statement()
                      : parse_statement()};
  if (tokenizer_.peek().type != TokenType::Else) {
    return std::make_shared<ast::IfStatement>(file_name_, location_, test,
                                              consequent, nullptr);
  }
  tokenizer_.next();
  auto alternate{tokenizer_.peek().type == TokenType::CurlyOpen
                     ? parse_block_statement()
                     : parse_statement()};
  return std::make_shared<ast::IfStatement>(file_name_, location_, test,
                                            consequent, alternate);
}

auto Parser::parse_variable_declaration()
    -> std::shared_ptr<ast::VariableDeclaration> {
  auto token{tokenizer_.next()};
  if (token.type != TokenType::Var) {
    throw std::runtime_error("Expected var");
  }
  auto identifier{parse_identifier()};
  if (tokenizer_.next().type != TokenType::Equals) {
    throw std::runtime_error("Expected =");
  }
  auto expression{parse_expression()};
  consume_semicolon();
  auto declarator{std::make_shared<ast::VariableDeclarator>(
      file_name_, location_, identifier, expression)};
  std::vector<std::shared_ptr<ast::VariableDeclarator>> declarators{declarator};
  return std::make_shared<ast::VariableDeclaration>(file_name_, location_,
                                                    declarators);
}

auto Parser::optional_parse_identifier()
    -> std::optional<std::shared_ptr<ast::Identifier>> {
  auto token{tokenizer_.peek()};
  if (token.type != TokenType::Identifier) {
    return {};
  }
  return parse_identifier();
}

auto Parser::parse_identifier() -> std::shared_ptr<ast::Identifier> {
  auto token{tokenizer_.next()};
  if (token.type != TokenType::Identifier) {
    throw std::runtime_error("Expected identifier");
  }
  return std::make_shared<ast::Identifier>(file_name_, location_, token.value);
}

auto Parser::optional_parse_numeric_literal()
    -> std::optional<std::shared_ptr<ast::Literal>> {
  auto token{tokenizer_.peek()};
  if (token.type != TokenType::NumericLiteral) {
    return {};
  }
  return parse_numeric_literal();
}

auto Parser::parse_numeric_literal() -> std::shared_ptr<ast::Literal> {
  auto token{tokenizer_.next()};
  if (token.type != TokenType::NumericLiteral) {
    throw std::runtime_error("Expected numeric literal");
  }
  return std::make_shared<ast::Literal>(file_name_, location_,
                                        std::stoi(token.value));
}

auto Parser::parse_expression() -> std::shared_ptr<ast::Expression> {
  std::optional<std::shared_ptr<ast::Expression>> optional_expr{
      optional_parse_identifier()};

  if (!optional_expr) {
    optional_expr = optional_parse_numeric_literal();
  }

  auto expr{*optional_expr};
  auto next{tokenizer_.peek()};
  if (is_binary_operator(next.type)) {
    tokenizer_.next();
    return std::make_shared<ast::BinaryExpression>(
        file_name_, location_, to_binary_operator(next.type), expr,
        parse_expression());
  }
  return expr;
}

void Parser::consume_semicolon() {
  if (tokenizer_.next().type != TokenType::Semicolon) {
    throw std::runtime_error("Expected ;");
  }
}

}  // namespace ctjs
