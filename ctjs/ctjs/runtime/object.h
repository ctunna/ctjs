#pragma once

#include <map>
#include <string>
#include <string_view>

namespace ctjs {
class Value;

class Object {
 public:
  virtual ~Object() = default;

  auto get_property(std::string_view name) -> Value;
  void set_property(std::string_view name, Value value);
  auto operator[](std::string_view name) -> Value&;
  [[nodiscard]] auto has_property(std::string_view name) const -> bool;
  [[nodiscard]] auto properties() const -> std::map<std::string, Value, std::less<>> const&;
  auto begin() -> std::map<std::string, Value>::iterator;
  auto end() -> std::map<std::string, Value>::iterator;

  [[nodiscard]] virtual auto to_string() const -> std::string;

 private:
  std::map<std::string, Value, std::less<>> properties_;
};
}  // namespace ctjs
