#include "ctjs/runtime/value.h"

namespace ctjs {
Value::Value(int value) : type_{Type::kInt}, int_value_(value) {}

Value::Value(bool value) : type_{Type::kBoolean}, bool_value_(value) {}

Value::Value(Function value) : type_{Type::kFunction}, function_value_(value) {}

Value::Value(std::string value) : type_{Type::kString}, string_value_(value) {}

auto Value::operator+(const Value& other) const -> Value {
  auto result{other.int_value_ + int_value_};
  return Value(result);
}

auto Value::operator-(const Value& other) const -> Value {
  auto result{int_value_ - other.int_value_};
  return Value(result);
}

auto Value::operator*(const Value& other) const -> Value {
  auto result{int_value_ * other.int_value_};
  return Value(result);
}

auto Value::operator>(const Value& other) const -> bool {
  return int_value_ > other.int_value_;
}

auto Value::operator<(const Value& other) const -> bool {
  return int_value_ < other.int_value_;
}

auto Value::operator==(const Value& other) const -> bool {
  return int_value_ == other.int_value_;
}

auto Value::to_string() const -> std::string {
  switch (type_) {
    case Type::kInt:
      return std::to_string(int_value_);
    case Type::kBoolean:
      return bool_value_ ? "true" : "false";
    case Type::kFunction:
      return "function()";
    case Type::kString:
      return "\"" + string_value_ + "\"";
    default:
      return "undefined";
  }
}
}  // namespace ctjs
