#pragma once

#include <string>
#include <variant>

#include "ctjs/runtime/array.h"
#include "ctjs/runtime/function.h"
#include "ctjs/runtime/object.h"

namespace ctjs {

class Value {
 public:
  Value() = default;
  Value(int value);
  Value(bool value);
  Value(std::string value);
  Value(Function value);
  Value(Object value);
  Value(Array value);

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
  std::variant<int, bool, std::string, Function, Object, Array> value_;
};
}  // namespace ctjs
