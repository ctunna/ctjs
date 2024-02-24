#include "ctjs/tokenizer.h"

#include <iostream>
#include <vector>

#include "catch2/catch_testmacros.hpp"

using ctjs::ast::TokenType;

namespace ctjs {
auto var() -> Token { return {TokenType::Var, "var", 0, 0}; }

auto identifier(std::string_view value) -> Token {
  return {TokenType::Identifier, value, 0, 0};
}

auto equals() -> Token { return {TokenType::Equals, "=", 0, 0}; }

auto semicolon() -> Token { return {TokenType::Semicolon, ";", 0, 0}; }

auto numeric_literal(std::string_view value) -> Token {
  return {TokenType::NumericLiteral, value, 0, 0};
}

auto plus() -> Token { return {TokenType::Plus, "+", 0, 0}; }

auto times() -> Token { return {TokenType::Asterisk, "*", 0, 0}; }

TEST_CASE("tokenizer consumes tokens") {
  Tokenizer tokenizer("var foo = 1 + 2; var bar = foo * foo;");
  std::vector<Token> expected{var(),
                              identifier("foo"),
                              equals(),
                              numeric_literal("1"),
                              plus(),
                              numeric_literal("2"),
                              semicolon(),
                              var(),
                              identifier("bar"),
                              equals(),
                              identifier("foo"),
                              times(),
                              identifier("foo"),
                              semicolon()};
  auto const actual{tokenizer.consume_all()};
  CHECK(expected == actual);
}

TEST_CASE("tokenizer consumes if") {
  Tokenizer tokenizer("if (x > 1) { return 1; }");
  auto const actual{tokenizer.consume_all()};
  for (auto const &token : actual) {
    std::cout << token.value << std::endl;
  }
}

}  // namespace ctjs
