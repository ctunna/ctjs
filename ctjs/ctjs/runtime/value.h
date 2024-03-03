#pragma once

#include <string>
#include <variant>

#include "ctjs/runtime/function.h"

namespace ctjs {

class Value {
 public:
  Value() = default;
  Value(int value);
  Value(bool value);
  Value(Function value);
  Value(std::string value);

  auto operator+(const Value& other) const -> Value;
  auto operator-(const Value& other) const -> Value;
  auto operator*(const Value& other) const -> Value;
  auto operator>(const Value& other) const -> bool;
  auto operator<(const Value& other) const -> bool;
  auto operator==(const Value& other) const -> bool;

  explicit operator bool() const;

  template <typename T>
  auto get() const -> T {
    return std::get<T>(value_);
  }

  auto to_string() const -> std::string;

 private:
  std::variant<int, bool, Function, std::string> value_;
};
}  // namespace ctjs
