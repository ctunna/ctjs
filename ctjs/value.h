#pragma once

#include <string>

namespace ctjs {
class Value {
 public:
  Value() = default;
  Value(int value);
  Value(bool value);

  auto operator+(const Value& other) const -> Value;
  auto operator>(const Value& other) const -> bool;

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

  [[maybe_unused]] bool defined_{};
  [[maybe_unused]] Type type_{Type::kUndefined};
  int int_value_{};
  bool bool_value_{};
};
}  // namespace ctjs
