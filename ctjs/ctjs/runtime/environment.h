#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

#include "ctjs/runtime/value.h"

namespace ctjs {
class Environment {
 public:
  auto get(std::string const& name) const -> Value;
  void set(std::string const& name, Value value);

  void to_string();

 private:
  std::unordered_map<std::string, Value> scope_;
};
using EnvironmentPtr = std::variant<std::shared_ptr<Environment>>;
}  // namespace ctjs