#include "ctjs/parser.h"

#include <iostream>

#include "ctjs/ast/assignment_expression.h"
#include "ctjs/ast/binary_expression.h"
#include "ctjs/ast/call_expression.h"
#include "ctjs/ast/identifier.h"

using ctjs::ast::BinaryOperator;
using ctjs::ast::TokenType;

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
  std::vector<ast::StatementPtr> statements;
  while (tokenizer_.ready()) {
    statements.push_back(parse_statement());
  }
  return std::make_shared<ast::Program>(file_name, location_, statements);
}

auto Parser::parse_statement() -> ast::StatementPtr {
  auto token{tokenizer_.peek()};
  switch (token.type) {
    case TokenType::Var:
      return parse_variable_declaration();
    case TokenType::If:
      return parse_if_statement();
    case TokenType::CurlyOpen:
      return parse_block_statement();
    case TokenType::While:
      return parse_while_statement();
    case TokenType::Function:
      return parse_function_declaration();
    case TokenType::Return:
      return parse_return_statement();
    default:
      return parse_expression_statement();
  }
}

auto Parser::parse_return_statement() -> std::shared_ptr<ast::ReturnStatement> {
  consume_token(TokenType::Return);
  if (expect_token(TokenType::Semicolon)) {
    consume_token(TokenType::Semicolon);
    return std::make_shared<ast::ReturnStatement>(file_name, location_,
                                                  std::nullopt);
  }
  auto expression{parse_expression()};
  consume_token(TokenType::Semicolon);
  return std::make_shared<ast::ReturnStatement>(file_name, location_,
                                                expression);
}

auto Parser::parse_function_declaration()
    -> std::shared_ptr<ast::FunctionDeclaration> {
  consume_token(TokenType::Function);
  auto identifier{parse_identifier()};
  consume_token(TokenType::ParenOpen);
  std::vector<ast::IdentifierPtr> params;
  while (!expect_token(TokenType::ParenClose)) {
    params.push_back(parse_identifier());
    if (expect_token(TokenType::Comma)) {
      consume_token(TokenType::Comma);
    }
  }
  consume_token(TokenType::ParenClose);
  auto body{parse_block_statement()};
  return std::make_shared<ast::FunctionDeclaration>(file_name, location_,
                                                    identifier, params, body);
}

auto Parser::parse_expression_statement()
    -> std::shared_ptr<ast::ExpressionStatement> {
  auto expression{parse_expression()};
  consume_token(TokenType::Semicolon);
  return std::make_shared<ast::ExpressionStatement>(file_name, location_,
                                                    expression);
}

auto Parser::parse_while_statement() -> std::shared_ptr<ast::WhileStatement> {
  consume_token(TokenType::While);
  consume_token(TokenType::ParenOpen);
  auto test{parse_expression()};
  consume_token(TokenType::ParenClose);
  auto body{parse_statement()};
  return std::make_shared<ast::WhileStatement>(file_name, location_, test,
                                               body);
}

auto Parser::parse_block_statement() -> std::shared_ptr<ast::BlockStatement> {
  consume_token(TokenType::CurlyOpen);
  std::vector<ast::StatementPtr> statements;
  while (!expect_token(TokenType::CurlyClose)) {
    statements.push_back(parse_statement());
  }
  consume_token(TokenType::CurlyClose);
  return std::make_shared<ast::BlockStatement>(file_name, location_,
                                               statements);
}

auto Parser::parse_if_statement() -> std::shared_ptr<ast::IfStatement> {
  consume_token(TokenType::If);
  consume_token(TokenType::ParenOpen);
  auto test{parse_expression()};
  consume_token(TokenType::ParenClose);
  auto consequent{parse_statement()};
  if (!expect_token(TokenType::Else)) {
    return std::make_shared<ast::IfStatement>(file_name, location_, test,
                                              consequent, std::nullopt);
  }
  consume_token(TokenType::Else);
  auto alternate{parse_statement()};
  return std::make_shared<ast::IfStatement>(file_name, location_, test,
                                            consequent, alternate);
}

auto Parser::parse_variable_declaration()
    -> std::shared_ptr<ast::VariableDeclaration> {
  consume_token(TokenType::Var);
  auto identifier{parse_identifier()};
  consume_token(TokenType::Equals);
  auto expression{parse_expression()};
  consume_token(TokenType::Semicolon);
  auto declarator{std::make_shared<ast::VariableDeclarator>(
      file_name, location_, identifier, expression)};
  std::vector<ast::VariableDeclaratorPtr> declarators{declarator};
  return std::make_shared<ast::VariableDeclaration>(file_name, location_,
                                                    declarators);
}

auto Parser::optional_parse_identifier()
    -> std::optional<std::shared_ptr<ast::Identifier>> {
  if (!expect_token(TokenType::Identifier)) {
    return {};
  }
  return parse_identifier();
}

auto Parser::parse_identifier() -> std::shared_ptr<ast::Identifier> {
  auto token{consume_token(TokenType::Identifier)};
  return std::make_shared<ast::Identifier>(file_name, location_, token.value);
}

auto Parser::optional_parse_numeric_literal()
    -> std::optional<std::shared_ptr<ast::Literal>> {
  auto token{tokenizer_.peek()};
  if (!expect_token(TokenType::NumericLiteral)) {
    return {};
  }
  return parse_numeric_literal();
}

auto Parser::parse_numeric_literal() -> std::shared_ptr<ast::Literal> {
  auto token{consume_token(TokenType::NumericLiteral)};
  return std::make_shared<ast::Literal>(file_name, location_,
                                        std::stoi(token.value));
}

auto Parser::optional_parse_string_literal()
    -> std::optional<std::shared_ptr<ast::Literal>> {
  auto token{tokenizer_.peek()};
  if (!expect_token(TokenType::StringLiteral)) {
    return {};
  }
  return parse_string_literal();
}

auto Parser::parse_string_literal() -> std::shared_ptr<ast::Literal> {
  auto token{consume_token(TokenType::StringLiteral)};
  return std::make_shared<ast::Literal>(file_name, location_, token.value);
}

auto Parser::parse_expression() -> ast::ExpressionPtr {
  std::optional<ast::ExpressionPtr> optional_expr{optional_parse_identifier()};

  if (optional_expr && expect_token(TokenType::Equals)) {
    consume_token(TokenType::Equals);
    return std::make_shared<ast::AssignmentExpression>(
        file_name, location_, *optional_expr, parse_expression());
  }

  if (optional_expr && expect_token(TokenType::ParenOpen)) {
    consume_token(TokenType::ParenOpen);
    std::vector<ast::ExpressionPtr> args;
    while (!expect_token(TokenType::ParenClose)) {
      args.push_back(parse_expression());
      if (expect_token(TokenType::Comma)) {
        consume_token(TokenType::Comma);
      }
    }
    consume_token(TokenType::ParenClose);
    optional_expr = std::make_shared<ast::CallExpression>(file_name, location_,
                                                          *optional_expr, args);
  }

  if (!optional_expr) {
    optional_expr = optional_parse_numeric_literal();
  }

  if (!optional_expr) {
    optional_expr = optional_parse_string_literal();
  }

  auto expr{*optional_expr};
  auto next{tokenizer_.peek()};
  if (is_binary_operator(next.type)) {
    tokenizer_.next();
    return std::make_shared<ast::BinaryExpression>(
        file_name, location_, to_binary_operator(next.type), expr,
        parse_expression());
  }
  return expr;
}

auto Parser::consume_token(TokenType type) -> Token {
  auto token{tokenizer_.next()};
  if (token.type != type) {
    throw std::runtime_error("Expected token of type " + to_string(type));
  }
  return token;
}

auto Parser::expect_token(TokenType type) -> std::optional<Token> {
  auto token{tokenizer_.peek()};
  if (token.type != type) {
    return {};
  }
  return token;
}
}  // namespace ctjs
