#include "value.h"

namespace ctjs {
Value::Value(int value)
    : defined_(true), type_{Type::kInt}, int_value_(value) {}

Value::Value(bool value)
    : defined_(true), type_{Type::kBoolean}, bool_value_(value) {}

auto Value::operator+(const Value& other) const -> Value {
  auto result{other.int_value_ + int_value_};
  return Value(result);
}

auto Value::operator>(const Value& other) const -> bool {
  return int_value_ > other.int_value_;
}

auto Value::to_string() const -> std::string {
  return std::to_string(int_value_);
}
}  // namespace ctjs
