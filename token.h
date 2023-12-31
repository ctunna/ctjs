#pragma once

#include "token_type.h"
#include <istream>

class Token {
public:
  explicit Token(TokenType type, std::string value, size_t line_no, size_t column) : type(type), value(value), line_no(line_no), column(column) {}

private:
  TokenType type;
  std::string value;
  size_t line_no;
  size_t column;
};
