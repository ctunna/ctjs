#pragma once

#include <string>

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

  auto to_string() const -> std::string;

  template <typename T>
  auto coerce() const -> T {
    if constexpr (std::is_same_v<T, int>) {
      switch (type_) {
        case Type::kInt:
          return int_value_;
        case Type::kBoolean:
          return bool_value_ ? 1 : 0;
        default:
          return 0;
      }
      return int_value_;
    } else if constexpr (std::is_same_v<T, bool>) {
      switch (type_) {
        case Type::kInt:
          return int_value_ != 0;
        case Type::kBoolean:
          return bool_value_;
        default:
          break;
      }
      return bool_value_;
    } else if constexpr (std::is_same_v<T, Function>) {
      if (type_ == Type::kFunction) {
        return function_value_;
      }
      throw std::runtime_error{"Value is not a function"};
    } else {
      static_assert(std::is_same_v<T, int> || std::is_same_v<T, bool> ||
                    std::is_same_v<T, Function>);
    }
  }

 private:
  enum class Type {
    kUndefined,
    kInt,
    kFloat,
    kString,
    kObject,
    kArray,
    kFunction,
    kNativeFunction,
    kBoolean,
    kNull
  };

  Type type_{Type::kUndefined};
  int int_value_{};
  bool bool_value_{};
  Function function_value_{};
  std::string string_value_{};
};
}  // namespace ctjs
