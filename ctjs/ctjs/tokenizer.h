#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "ctjs/token.h"

namespace ctjs {

class Tokenizer {
 public:
  Tokenizer(std::string_view source);

  Tokenizer(const Tokenizer &) = delete;
  Tokenizer(Tokenizer &&) = delete;
  auto operator=(const Tokenizer &) -> Tokenizer & = delete;
  auto operator=(Tokenizer &&) -> Tokenizer & = delete;

  auto ready() -> bool;

  auto consume_all() -> std::vector<Token>;

  auto peek() -> Token;

  auto next() -> Token;

  auto line() -> size_t;

  auto column() -> size_t;

 private:
  auto consume_string_literal() -> std::string;

  auto consume_numeric_literal() -> std::string;

  auto consume_identifier() -> std::string;

  auto consume_line_comment() -> void;

  auto is_identifier_char() -> bool;

  auto is_alpha() -> bool;

  auto is_digit() -> bool;

  auto is_char(char c) -> bool;

  auto is_whitespace() -> bool;

  auto is_line_comment() -> bool;

  struct State {
    size_t position{0};
    size_t line{1};
    size_t col_start{0};
  };

  State state_;
  std::string source_;
};
}  // namespace ctjs
