#pragma once

#include <ostream>
#include <string>
#include <string_view>

#include "token_type.h"

class Token {
 public:
  Token(TokenType type, std::string_view value, size_t line_no, size_t column)
      : type(type), value(value), line_no(line_no), column(column) {}

  auto operator==(const Token &other) const -> bool {
    return type == other.type && value == other.value;
  }

  friend auto operator<<(std::ostream &os, const Token &token)
      -> std::ostream & {
    os << "Token(" << static_cast<int>(token.type) << ", " << token.value
       << ")";
    return os;
  }

  TokenType type;
  std::string value;
  size_t line_no;
  size_t column;
};
