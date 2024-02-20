#pragma once

#include <istream>
#include <string>
#include <string_view>
#include <unordered_map>

#include "ctjs/token.h"
#include "ctjs/token_type.h"

namespace ctjs {

class Tokenizer {
 public:
  Tokenizer(const std::string_view source);

  Tokenizer(const Tokenizer &) = delete;
  Tokenizer(Tokenizer &&) = delete;
  Tokenizer &operator=(const Tokenizer &) = delete;
  Tokenizer &operator=(Tokenizer &&) = delete;

  auto ready() -> bool;

  auto consume_all() -> std::vector<Token>;

  auto peek() -> Token;

  auto next() -> Token;

 private:
  auto consume_string_literal() -> std::string;

  auto consume_numeric_literal() -> std::string;

  auto consume_identifier() -> std::string;

  auto is_identifier_char() -> bool;

  auto is_alpha() -> bool;

  auto is_digit() -> bool;

  auto is_char(char c) -> bool;

  auto is_whitespace() -> bool;

  size_t position_{0};
  std::string_view source_;
};
}  // namespace ctjs
