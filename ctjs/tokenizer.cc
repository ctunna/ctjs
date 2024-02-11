#include "tokenizer.h"

namespace ctjs {
static std::unordered_map<std::string, TokenType> const three_char_tokens{
    {"===", TokenType::EqualsEqualsEquals},
};
static std::unordered_map<std::string, TokenType> const two_char_tokens{
    {">=", TokenType::GreaterThanEquals},
    {"<=", TokenType::LessThanEquals},
    {"!=", TokenType::ExclamationMark},
    {"==", TokenType::EqualsEquals}};
static std::unordered_map<std::string, TokenType> const one_char_tokens{
    {"(", TokenType::ParenOpen},    {")", TokenType::ParenClose},
    {"[", TokenType::BracketOpen},  {"]", TokenType::BracketClose},
    {"{", TokenType::CurlyOpen},    {"}", TokenType::CurlyClose},
    {".", TokenType::Period},       {",", TokenType::Comma},
    {"-", TokenType::Minus},        {"*", TokenType::Asterisk},
    {";", TokenType::Semicolon},    {"=", TokenType::Equals},
    {"+", TokenType::Plus},         {">", TokenType::GreaterThan},
    {"<", TokenType::LessThan},     {"!", TokenType::ExclamationMark},
    {"?", TokenType::QuestionMark}, {":", TokenType::Colon}};
static std::unordered_map<std::string, TokenType> const keyword_tokens{
    {"var", TokenType::Var},       {"let", TokenType::Let},
    {"const", TokenType::Const},   {"if", TokenType::If},
    {"else", TokenType::Else},     {"function", TokenType::Function},
    {"return", TokenType::Return}, {"while", TokenType::While},
    {"for", TokenType::For},       {"in", TokenType::In},
    {"new", TokenType::New}};

Tokenizer::Tokenizer(const std::string_view source) : source_(source) {}

auto Tokenizer::ready() -> bool { return position_ < source_.size(); }

auto Tokenizer::consume_all() -> std::vector<Token> {
  std::vector<Token> tokens;
  while (ready()) {
    tokens.push_back(next());
  }
  return tokens;
}

auto Tokenizer::peek() -> Token {
  auto position{position_};
  auto token{next()};
  position_ = position;
  return token;
}

auto Tokenizer::next() -> Token {
  while (is_whitespace()) {
    position_++;
  }

  std::vector<std::unordered_map<std::string, TokenType>> maps{
      keyword_tokens, three_char_tokens, two_char_tokens, one_char_tokens};

  for (const auto &map : maps) {
    for (const auto &[str, token_type] : map) {
      if (source_.substr(position_, str.size()) == str) {
        position_ += str.size();
        return {token_type, str, 0, 0};
      }
    }
  }

  if (is_digit()) {
    auto number = consume_numeric_literal();
    return {TokenType::NumericLiteral, number, 0, 0};
  }

  if (is_identifier_char()) {
    auto identifier = consume_identifier();
    return {TokenType::Identifier, identifier, 0, 0};
  }

  if (position_ >= source_.size()) {
    return {TokenType::Eof, "", 0, 0};
  }

  throw std::runtime_error("Unknown token");
}

auto Tokenizer::consume_numeric_literal() -> std::string {
  std::string number;
  while (is_digit()) {
    number += source_[position_];
    position_++;
  }
  return number;
}

auto Tokenizer::consume_identifier() -> std::string {
  std::string identifier;

  while (is_identifier_char()) {
    identifier += source_[position_];
    position_++;
  }

  return identifier;
}

auto Tokenizer::is_identifier_char() -> bool {
  return is_alpha() || is_digit() || is_char('_');
}

auto Tokenizer::is_alpha() -> bool {
  return (source_[position_] >= 'a' && source_[position_] <= 'z') ||
         (source_[position_] >= 'A' && source_[position_] <= 'Z');
}

auto Tokenizer::is_digit() -> bool {
  return source_[position_] >= '0' && source_[position_] <= '9';
}

auto Tokenizer::is_char(char c) -> bool { return source_[position_] == c; }

auto Tokenizer::is_whitespace() -> bool {
  return source_[position_] == ' ' || source_[position_] == '\t' ||
         source_[position_] == '\n';
}

}  // namespace ctjs