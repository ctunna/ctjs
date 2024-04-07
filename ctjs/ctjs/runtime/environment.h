#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

#include "ctjs/runtime/value.h"
#include "ctjs/util/box.h"

namespace ctjs {
class Environment {
 public:
  Environment() = default;

  explicit Environment(Environment* parent);

  Environment(Environment const&) = default;
  Environment(Environment&&) = default;
  auto operator=(Environment const&) -> Environment& = default;
  auto operator=(Environment&&) -> Environment& = default;
  ~Environment() = default;

  void define(std::string const& name, Value value);
  auto get(std::string const& name) const -> Value;
  void set(std::string const& name, Value value);

  void print();

 private:
  std::unordered_map<std::string, Value> scope_;
  Environment* parent_{nullptr};
};
}  // namespace ctjs
