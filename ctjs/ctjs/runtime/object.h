#pragma once

#include <map>
#include <string>
#include <string_view>

namespace ctjs {
class Value;

class Object {
 public:
  auto get_property(const std::string_view name) const -> Value;
  void set_property(const std::string_view name, const Value& value);
  auto operator[](const std::string_view name) -> Value&;
  auto has_property(const std::string_view name) const -> bool;
  auto properties() const -> std::map<std::string, Value> const&;
  auto begin() -> std::map<std::string, Value>::iterator;
  auto end() -> std::map<std::string, Value>::iterator;

 private:
  std::map<std::string, Value> properties_;
};
}  // namespace ctjs