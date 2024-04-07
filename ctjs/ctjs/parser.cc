#include "ctjs/parser.h"

#include <iostream>

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

Parser::Parser(std::string file_name, std::string_view source)
    : file_name_(std::move(file_name)), tokenizer_(source) {}

auto Parser::parse() -> util::Box<ast::Program> {
  std::vector<ast::Statement> statements;
  auto start{position()};
  while (tokenizer_.ready()) {
    statements.push_back(parse_statement());
  }
  auto end{position()};
  return ast::Program({file_name_, start, end}, statements);
}

auto Parser::parse_statement() -> ast::Statement {
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
    case TokenType::For:
      return parse_for_in_statement();
    case TokenType::Function:
      return parse_function_declaration();
    case TokenType::Return:
      return parse_return_statement();
    default:
      return parse_expression_statement();
  }
}

auto Parser::parse_return_statement() -> util::Box<ast::ReturnStatement> {
  auto start{position()};
  consume_token(TokenType::Return);
  if (expect_token(TokenType::Semicolon)) {
    consume_token(TokenType::Semicolon);
    auto end{position()};
    return ast::ReturnStatement({file_name_, start, end}, std::nullopt);
  }
  auto expression{parse_expression()};
  consume_token(TokenType::Semicolon);
  auto end{position()};
  return ast::ReturnStatement({file_name_, start, end}, expression);
}

auto Parser::parse_function_declaration()
    -> util::Box<ast::FunctionDeclaration> {
  auto start{position()};
  consume_token(TokenType::Function);
  auto identifier{parse_identifier()};
  consume_token(TokenType::ParenOpen);
  std::vector<ast::IdentifierVariant> params;
  while (!expect_token(TokenType::ParenClose)) {
    params.push_back(parse_identifier());
    if (expect_token(TokenType::Comma)) {
      consume_token(TokenType::Comma);
    }
  }
  consume_token(TokenType::ParenClose);
  auto body{parse_block_statement()};
  auto end{position()};
  return ast::FunctionDeclaration({file_name_, start, end}, identifier, params,
                                  body);
}

auto Parser::parse_expression_statement()
    -> util::Box<ast::ExpressionStatement> {
  auto start{position()};
  auto expression{parse_expression()};
  consume_token(TokenType::Semicolon);
  auto end{position()};
  return ast::ExpressionStatement({file_name_, start, end}, expression);
}

auto Parser::parse_while_statement() -> util::Box<ast::WhileStatement> {
  auto start{position()};
  consume_token(TokenType::While);
  consume_token(TokenType::ParenOpen);
  auto test{parse_expression()};
  consume_token(TokenType::ParenClose);
  auto body{parse_statement()};
  auto end{position()};
  return ast::WhileStatement({file_name_, start, end}, test, body);
}

auto Parser::parse_for_in_statement() -> util::Box<ast::ForInStatement> {
  auto start{position()};
  consume_token(TokenType::For);
  consume_token(TokenType::ParenOpen);
  consume_token(TokenType::Var);
  auto left{parse_identifier()};
  consume_token(TokenType::In);
  auto right{parse_expression()};
  consume_token(TokenType::ParenClose);
  auto body{parse_statement()};
  auto end{position()};
  return ast::ForInStatement({file_name_, start, end}, left, right, body);
}

auto Parser::parse_block_statement() -> util::Box<ast::BlockStatement> {
  auto start{position()};
  consume_token(TokenType::CurlyOpen);
  std::vector<ast::Statement> statements;
  while (!expect_token(TokenType::CurlyClose)) {
    statements.push_back(parse_statement());
  }
  consume_token(TokenType::CurlyClose);
  auto end{position()};
  return ast::BlockStatement({file_name_, start, end}, statements);
}

auto Parser::parse_if_statement() -> util::Box<ast::IfStatement> {
  auto start{position()};
  consume_token(TokenType::If);
  consume_token(TokenType::ParenOpen);
  auto test{parse_expression()};
  consume_token(TokenType::ParenClose);
  auto consequent{parse_statement()};
  if (!expect_token(TokenType::Else)) {
    auto end{position()};
    return ast::IfStatement({file_name_, start, end}, test, consequent,
                            std::nullopt);
  }
  consume_token(TokenType::Else);
  auto alternate{parse_statement()};
  auto end{position()};
  return ast::IfStatement({file_name_, start, end}, test, consequent,
                          alternate);
}

auto Parser::parse_variable_declaration()
    -> util::Box<ast::VariableDeclaration> {
  auto start{position()};
  consume_token(TokenType::Var);
  auto identifier{parse_identifier()};
  // TODO: Assignment is optional.
  consume_token(TokenType::Equals);
  auto expression{parse_expression()};
  consume_token(TokenType::Semicolon);
  auto end{position()};
  ast::VariableDeclarator declarator{
      {file_name_, start, end}, identifier, expression};
  std::vector<ast::VariableDeclaratorVariant> declarators{declarator};
  return ast::VariableDeclaration({file_name_, start, end}, declarators);
}

auto Parser::optional_parse_identifier()
    -> std::optional<util::Box<ast::Identifier>> {
  if (!expect_token(TokenType::Identifier)) {
    return {};
  }
  return parse_identifier();
}

auto Parser::parse_identifier() -> util::Box<ast::Identifier> {
  auto start{position()};
  auto token{consume_token(TokenType::Identifier)};
  auto end{position()};
  return ast::Identifier({file_name_, start, end}, token.value);
}

auto Parser::optional_parse_numeric_literal()
    -> std::optional<util::Box<ast::Literal>> {
  auto token{tokenizer_.peek()};
  if (!expect_token(TokenType::NumericLiteral)) {
    return {};
  }
  return parse_numeric_literal();
}

auto Parser::parse_numeric_literal() -> util::Box<ast::Literal> {
  auto start{position()};
  auto token{consume_token(TokenType::NumericLiteral)};
  auto end{position()};
  return ast::Literal({file_name_, start, end}, std::stoi(token.value));
}

auto Parser::optional_parse_string_literal()
    -> std::optional<util::Box<ast::Literal>> {
  auto token{tokenizer_.peek()};
  if (!expect_token(TokenType::StringLiteral)) {
    return {};
  }
  return parse_string_literal();
}

auto Parser::parse_string_literal() -> util::Box<ast::Literal> {
  auto start{position()};
  auto token{consume_token(TokenType::StringLiteral)};
  auto end{position()};
  return ast::Literal({file_name_, start, end}, token.value);
}

auto Parser::optional_parse_array_expression()
    -> std::optional<util::Box<ast::ArrayExpression>> {
  if (!expect_token(TokenType::BracketOpen)) {
    return {};
  }
  return parse_array_expression();
}

auto Parser::parse_array_expression() -> util::Box<ast::ArrayExpression> {
  auto start{position()};
  consume_token(TokenType::BracketOpen);
  std::vector<ast::Expression> elements;
  while (!expect_token(TokenType::BracketClose)) {
    elements.push_back(parse_expression());
    if (expect_token(TokenType::Comma)) {
      consume_token(TokenType::Comma);
    }
  }
  consume_token(TokenType::BracketClose);
  auto end{position()};
  return ast::ArrayExpression({file_name_, start, end}, elements);
}

auto Parser::parse_function_expression() -> util::Box<ast::FunctionExpression> {
  auto start{position()};
  consume_token(TokenType::Function);
  consume_token(TokenType::ParenOpen);
  std::vector<ast::IdentifierVariant> params;
  while (!expect_token(TokenType::ParenClose)) {
    params.push_back(parse_identifier());
    if (expect_token(TokenType::Comma)) {
      consume_token(TokenType::Comma);
    }
  }
  consume_token(TokenType::ParenClose);
  auto body{parse_block_statement()};
  auto end{position()};
  return ast::FunctionExpression({file_name_, start, end}, params, body);
}

auto Parser::optional_parse_function_expression()
    -> std::optional<util::Box<ast::FunctionExpression>> {
  if (!expect_token(TokenType::Function)) {
    return {};
  }
  return parse_function_expression();
}

auto Parser::optional_parse_object_expression()
    -> std::optional<util::Box<ast::ObjectExpression>> {
  if (!expect_token(TokenType::CurlyOpen)) {
    return {};
  }
  return parse_object_expression();
}

auto Parser::parse_object_expression() -> util::Box<ast::ObjectExpression> {
  auto start{position()};
  consume_token(TokenType::CurlyOpen);
  std::vector<ast::Property> properties;
  while (!expect_token(TokenType::CurlyClose)) {
    auto key{parse_identifier()};
    consume_token(TokenType::Colon);
    auto value{parse_expression()};
    properties.emplace_back(key, value);
    if (expect_token(TokenType::Comma)) {
      consume_token(TokenType::Comma);
    }
  }
  consume_token(TokenType::CurlyClose);
  auto end{position()};
  return ast::ObjectExpression{{file_name_, start, end}, properties};
}

auto Parser::parse_expression() -> ast::Expression {
  auto start{position()};
  std::optional<ast::Expression> optional_expr{optional_parse_identifier()};

  if (optional_expr && expect_token(TokenType::Equals)) {
    consume_token(TokenType::Equals);
    auto end{position()};
    return ast::AssignmentExpression({file_name_, start, end}, *optional_expr,
                                     parse_expression());
  }

  if (optional_expr && expect_token(TokenType::ParenOpen)) {
    consume_token(TokenType::ParenOpen);
    std::vector<ast::Expression> args;
    while (!expect_token(TokenType::ParenClose)) {
      args.push_back(parse_expression());
      if (expect_token(TokenType::Comma)) {
        consume_token(TokenType::Comma);
      }
    }
    consume_token(TokenType::ParenClose);
    auto end{position()};
    optional_expr =
        ast::CallExpression({file_name_, start, end}, *optional_expr, args);
  }

  if (optional_expr && expect_token(TokenType::BracketOpen)) {
    consume_token(TokenType::BracketOpen);
    auto literal{parse_expression()};
    consume_token(TokenType::BracketClose);
    auto end{position()};
    optional_expr = ast::MemberExpression({file_name_, start, end},
                                          *optional_expr, literal);
  }

  if (optional_expr && expect_token(TokenType::Period)) {
    consume_token(TokenType::Period);
    auto id_start{position()};
    auto identifier{parse_identifier()};
    auto end{position()};
    auto literal{ast::Literal({file_name_, id_start, end}, identifier->name)};
    optional_expr = ast::MemberExpression({file_name_, start, end},
                                          *optional_expr, literal);
  }

  if (!optional_expr) {
    optional_expr = optional_parse_function_expression();
  }

  if (!optional_expr) {
    optional_expr = optional_parse_array_expression();
  }

  if (!optional_expr) {
    optional_expr = optional_parse_object_expression();
  }

  if (!optional_expr) {
    optional_expr = optional_parse_numeric_literal();
  }

  if (!optional_expr) {
    optional_expr = optional_parse_string_literal();
  }

  if (!optional_expr) {
    throw std::runtime_error("Unknown expression");
  }

  auto expr{*optional_expr};
  auto next{tokenizer_.peek()};
  if (is_binary_operator(next.type)) {
    tokenizer_.next();
    auto end{position()};
    return ast::BinaryExpression({file_name_, start, end},
                                 to_binary_operator(next.type), expr,
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

auto Parser::position() -> ast::Position {
  return ast::Position{tokenizer_.line(), tokenizer_.column()};
}
}  // namespace ctjs
