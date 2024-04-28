#include "ctjs/parser.h"

#include "ctjs/token_type.h"

using ctjs::ast::BinaryOperator;
using ctjs::ast::TokenType;

namespace ctjs {

auto to_binary_operator(TokenType type) -> ast::BinaryOperator {
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
      throw std::runtime_error("Unknown binary operator: " + to_token(type));
  }
}

auto is_binary_operator(TokenType type) -> bool {
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
    params.emplace_back(parse_identifier());
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

auto Parser::parse_identifier() -> util::Box<ast::Identifier> {
  auto start{position()};
  auto token{consume_token(TokenType::Identifier)};
  auto end{position()};
  return ast::Identifier({file_name_, start, end}, token.value);
}

auto Parser::parse_bool_literal() -> util::Box<ast::Literal> {
  auto start{position()};
  auto token{consume_token(TokenType::BoolLiteral)};
  auto end{position()};
  return ast::Literal({file_name_, start, end}, Value(token.value == "true"));
}

auto Parser::parse_numeric_literal() -> util::Box<ast::Literal> {
  auto start{position()};
  auto token{consume_token(TokenType::NumericLiteral)};
  auto end{position()};
  return ast::Literal({file_name_, start, end}, Value(std::stoi(token.value)));
}

auto Parser::parse_string_literal() -> util::Box<ast::Literal> {
  auto start{position()};
  auto token{consume_token(TokenType::StringLiteral)};
  auto end{position()};
  return ast::Literal({file_name_, start, end}, Value(token.value));
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
    params.emplace_back(parse_identifier());
    if (expect_token(TokenType::Comma)) {
      consume_token(TokenType::Comma);
    }
  }
  consume_token(TokenType::ParenClose);
  auto body{parse_block_statement()};
  auto end{position()};
  return ast::FunctionExpression({file_name_, start, end}, params, body);
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

auto Parser::parse_secondary_expression(ast::Expression lhs)
    -> ast::Expression {
  auto start{position()};
  auto next{tokenizer_.next()};
  switch (next.type) {
    case TokenType::Plus:
    case TokenType::Minus:
    case TokenType::Asterisk:
    case TokenType::Slash:
    case TokenType::EqualsEquals:
    case TokenType::LessThan:
    case TokenType::LessThanEquals:
    case TokenType::GreaterThan:
    case TokenType::GreaterThanEquals:
      return ast::BinaryExpression({file_name_, start, start},
                                   to_binary_operator(next.type),
                                   std::move(lhs), parse_expression());
    case TokenType::Period: {
      auto identifier{parse_identifier()};
      auto end{position()};
      auto prop{
          ast::Literal({file_name_, start, end}, Value(identifier->name))};
      return ast::MemberExpression({file_name_, start, start}, std::move(lhs),
                                   prop);
    }
    case TokenType::BracketOpen: {
      auto literal{parse_expression()};
      auto end{position()};
      auto expr{ast::MemberExpression({file_name_, start, end}, std::move(lhs),
                                      literal)};
      consume_token(TokenType::BracketClose);
      return expr;
    }
    case TokenType::ParenOpen: {
      std::vector<ast::Expression> arguments;
      while (!expect_token(TokenType::ParenClose)) {
        arguments.push_back(parse_expression());
        if (expect_token(TokenType::Comma)) {
          consume_token(TokenType::Comma);
        }
      }
      consume_token(TokenType::ParenClose);
      auto end{position()};
      return ast::CallExpression({file_name_, start, end}, std::move(lhs),
                                 arguments);
    }
    case TokenType::Equals: {
      auto expr{parse_expression()};
      auto end{position()};
      return ast::AssignmentExpression({file_name_, start, end}, std::move(lhs),
                                       expr);
    }
    default:
      throw std::runtime_error("Unknown secondary expression");
  }
}

auto Parser::parse_primary_expression() -> ast::Expression {
  auto next{tokenizer_.peek()};
  switch (next.type) {
    default:
      throw std::runtime_error("Unknown primary expression");
    case TokenType::Identifier:
      return parse_identifier();
    case TokenType::BoolLiteral:
      return parse_bool_literal();
    case TokenType::NumericLiteral:
      return parse_numeric_literal();
    case TokenType::StringLiteral:
      return parse_string_literal();
    case TokenType::BracketOpen:
      return parse_array_expression();
    case TokenType::CurlyOpen:
      return parse_object_expression();
    case TokenType::Function:
      return parse_function_expression();
    case TokenType::ParenOpen:
      consume_token(TokenType::ParenOpen);
      auto expression{parse_expression()};
      consume_token(TokenType::ParenClose);
      return expression;
  }
}

auto Parser::parse_expression() -> ast::Expression {
  auto expr{parse_primary_expression()};
  while (match_secondary_expression()) {
    expr = parse_secondary_expression(std::move(expr));
  }
  return expr;
}

auto Parser::match_secondary_expression() -> bool {
  auto type{tokenizer_.peek().type};
  return type == TokenType::Plus || type == TokenType::Minus ||
         type == TokenType::Asterisk || type == TokenType::Slash ||
         type == TokenType::EqualsEquals || type == TokenType::LessThan ||
         type == TokenType::LessThanEquals || type == TokenType::GreaterThan ||
         type == TokenType::GreaterThanEquals || type == TokenType::Period ||
         type == TokenType::BracketOpen || type == TokenType::ParenOpen ||
         type == TokenType::Equals;
}

auto Parser::consume_token(TokenType type) -> Token {
  auto token{tokenizer_.next()};
  if (token.type != type) {
    throw std::runtime_error("Expected token of type '" + to_token(type) +
                             "' but found '" + token.value + "' (" +
                             std::to_string(token.line) + ", " +
                             std::to_string(token.col) + ") " + file_name_);
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
