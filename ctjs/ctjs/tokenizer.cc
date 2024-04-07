#include "ctjs/tokenizer.h"

#include <regex>

using ctjs::ast::TokenType;

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

auto Tokenizer::ready() -> bool {
  return position_ < source_.size() && peek().type != TokenType::Eof;
}

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
    if (is_char('\n')) {
      line_++;
      col_ = 1;
    }
    position_++;
  }

  if (is_line_comment()) {
    consume_line_comment();
  }

  for (const auto &[token, token_type] : keyword_tokens) {
    std::regex re{token + "[^\\w]"};
    std::string str{source_.substr(position_, token.size() + 1)};
    if (std::regex_match(str, re) ||
        (str == token && position_ + token.size() == source_.size())) {
      position_ += token.size();
      return {token_type, token, line_, col_};
    }
  }

  std::vector<std::unordered_map<std::string, TokenType>> maps{
      three_char_tokens, two_char_tokens, one_char_tokens};

  for (const auto &map : maps) {
    for (const auto &[token, token_type] : map) {
      if (source_.substr(position_, token.size()) == token) {
        position_ += token.size();
        return {token_type, token, line_, col_};
      }
    }
  }

  if (is_digit()) {
    auto number{consume_numeric_literal()};
    return {TokenType::NumericLiteral, number, line_, col_};
  }

  if (is_identifier_char()) {
    auto identifier{consume_identifier()};
    return {TokenType::Identifier, identifier, line_, col_};
  }

  if (is_char('"')) {
    auto str{consume_string_literal()};
    return {TokenType::StringLiteral, str, line_, col_};
  }

  if (position_ >= source_.size()) {
    return {TokenType::Eof, "", line_, col_};
  }

  throw std::runtime_error("Unknown token");
}

auto Tokenizer::line() -> size_t { return line_; }

auto Tokenizer::column() -> size_t { return col_; }

auto Tokenizer::consume_string_literal() -> std::string {
  std::string str;
  if (is_char('"')) {
    position_++;
    while (!is_char('"')) {
      str += source_[position_];
      position_++;
    }
    position_++;
  }
  return str;
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

auto Tokenizer::consume_line_comment() -> void {
  while (is_line_comment()) {
    position_ += 2;
    // TODO: Handle CRLF
    while (!is_char('\n')) {
      position_++;
    }
    while (is_whitespace()) {
      if (is_char('\n')) {
        line_++;
        col_ = 1;
      }
      position_++;
    }
  }
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

auto Tokenizer::is_line_comment() -> bool {
  return source_.substr(position_, 2) == "//";
}

}  // namespace ctjs