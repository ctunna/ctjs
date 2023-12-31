#pragma once

#include "token_type.h"
#include <istream>
#include <string_view> 

class Tokenizer {
public:
  Tokenizer(const std::string_view source) : source_(source) {} 

  Tokenizer(const Tokenizer &) = delete;
  Tokenizer(Tokenizer &&) = delete;
  Tokenizer &operator=(const Tokenizer &) = delete;
  Tokenizer &operator=(Tokenizer &&) = delete;

  TokenType next() {
    while(is_whitespace()) {
      position_++;
    }

  }

private:



  bool is_whitespace() {
    return source_[position_] == ' ' || source_[position_] == '\t' || source_[position_] == '\n';
  }

  size_t position_ = 0;
  std::string_view source_;
};
