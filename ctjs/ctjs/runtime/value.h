#pragma once

#include <map>
#include <string>
#include <variant>

#include "ctjs/runtime/object.h"

namespace ctjs {

class Value {
 public:
  Value() = default;
  Value(int value);
  Value(bool value);
  Value(std::string value);
  Value(std::shared_ptr<Object> value);

  auto operator+(Value const& other) const -> Value;
  auto operator-(Value const& other) const -> Value;
  auto operator*(Value const& other) const -> Value;
  auto operator>(Value const& other) const -> bool;
  auto operator<(Value const& other) const -> bool;
  auto operator==(Value const& other) const -> bool;
  auto operator[](Value const& other) -> Value;

  explicit operator bool() const;

  template <typename T>
  auto get() const -> T {
    return std::get<T>(value_);
  }

  auto to_string() const -> std::string;

 private:
  std::variant<int, bool, std::string, std::shared_ptr<Object>> value_;
};
}  // namespace ctjs
