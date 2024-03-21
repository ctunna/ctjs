#pragma once

#include <ctjs/runtime/array.h>
#include <ctjs/runtime/function.h>
#include <ctjs/runtime/object.h>
#include <ctjs/runtime/value.h>

#include <string>

namespace ctjs {
template <typename T>
struct Coerce {
  auto operator()(int const& value) const -> T {
    if constexpr (std::is_same_v<T, int>) {
      return value;
    } else if constexpr (std::is_same_v<T, bool>) {
      return value != 0;
    } else if constexpr (std::is_same_v<T, std::string>) {
      return std::to_string(value);
    } else if constexpr (std::is_same_v<T, std::shared_ptr<Object>>) {
      throw std::runtime_error("Cannot coerce object to int");
    }
    throw std::runtime_error("Invalid coercion");
  }

  auto operator()(bool const& value) const -> T {
    if constexpr (std::is_same_v<T, int>) {
      return value ? 1 : 0;
    } else if constexpr (std::is_same_v<T, bool>) {
      return value;
    } else if constexpr (std::is_same_v<T, std::string>) {
      return value ? "true" : "false";
    } else if constexpr (std::is_same_v<T, std::shared_ptr<Object>>) {
      throw std::runtime_error("Cannot coerce object to bool");
    }
    throw std::runtime_error("Invalid coercion");
  }

  auto operator()(std::string const& value) const -> T {
    if constexpr (std::is_same_v<T, int>) {
      return std::stoi(value);
    } else if constexpr (std::is_same_v<T, bool>) {
      if (value == "true" || value == "false") {
        return value == "true";
      }
      throw std::runtime_error("Cannot coerce string to bool");
    } else if constexpr (std::is_same_v<T, std::string>) {
      return value;
    } else if constexpr (std::is_same_v<T, std::shared_ptr<Object>>) {
      throw std::runtime_error("Cannot coerce string to object");
    }
    throw std::runtime_error("Invalid coercion");
  }

  auto operator()(std::shared_ptr<Object> const& value) const -> T {
    if constexpr (std::is_same_v<T, int>) {
      throw std::runtime_error("Cannot coerce object to int");
    } else if constexpr (std::is_same_v<T, bool>) {
      return true;
    } else if constexpr (std::is_same_v<T, std::string>) {
      return "object";
    } else if constexpr (std::is_same_v<T, std::shared_ptr<Object>>) {
      return value;
    }
    throw std::runtime_error("Invalid coercion");
  }
};
}  // namespace ctjs
