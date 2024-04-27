#pragma once

#include <string>
#include <string_view>

#include "ctjs/token_type.h"

namespace ctjs {

class Token {
 public:
  Token(ast::TokenType type, std::string_view value, size_t line, size_t col)
      : type(type), value(value), line(line), col(col) {}

  auto operator==(const Token &other) const -> bool {
    return type == other.type && value == other.value;
  }

  [[nodiscard]] auto to_string() const -> std::string {
    return "Token(" + value + ", (line=" + std::to_string(line) +
           ", col=" + std::to_string(col) + "))";
  }

  ast::TokenType type;
  std::string value;
  size_t line;
  size_t col;
};
}  // namespace ctjs
