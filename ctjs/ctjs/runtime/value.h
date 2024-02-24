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

  template <typename T>
  auto coerce() const -> T {
    // TOOD: Coerce type, don't get
    return std::get<T>(value_);
  }

  auto to_string() const -> std::string;

 private:
  std::variant<int, bool, Function, std::string> value_;
};
}  // namespace ctjs
