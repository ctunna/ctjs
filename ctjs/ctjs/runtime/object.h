#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

namespace ctjs {
class Value;

class Object {
 public:
  auto get_property(const std::string_view name) const -> Value;
  void set_property(const std::string_view name, const Value& value);
  auto operator[](const std::string_view name) -> Value&;
  auto has_property(const std::string_view name) const -> bool;
  auto properties() const -> const std::unordered_map<std::string, Value>&;

 private:
  std::unordered_map<std::string, Value> properties_;
};
}  // namespace ctjs