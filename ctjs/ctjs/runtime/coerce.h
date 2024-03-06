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
    } else if constexpr (std::is_same_v<T, Function>) {
      throw std::runtime_error("Cannot coerce function to int");
    } else if constexpr (std::is_same_v<T, Object>) {
      throw std::runtime_error("Cannot coerce object to int");
    } else if constexpr (std::is_same_v<T, Array>) {
      throw std::runtime_error("Cannot coerce array to int");
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
    } else if constexpr (std::is_same_v<T, Function>) {
      throw std::runtime_error("Cannot coerce function to bool");
    } else if constexpr (std::is_same_v<T, Object>) {
      throw std::runtime_error("Cannot coerce object to bool");
    } else if constexpr (std::is_same_v<T, Array>) {
      throw std::runtime_error("Cannot coerce array to bool");
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
    } else if constexpr (std::is_same_v<T, Function>) {
      throw std::runtime_error("Cannot coerce string to function");
    } else if constexpr (std::is_same_v<T, Object>) {
      throw std::runtime_error("Cannot coerce string to object");
    } else if constexpr (std::is_same_v<T, Array>) {
      throw std::runtime_error("Cannot coerce string to array");
    }
    throw std::runtime_error("Invalid coercion");
  }

  auto operator()(Function const& value) const -> T {
    if constexpr (std::is_same_v<T, int>) {
      throw std::runtime_error("Cannot coerce function to int");
    } else if constexpr (std::is_same_v<T, bool>) {
      return true;
    } else if constexpr (std::is_same_v<T, std::string>) {
      return "function";
    } else if constexpr (std::is_same_v<T, Function>) {
      return value;
    } else if constexpr (std::is_same_v<T, Object>) {
      throw std::runtime_error("Cannot coerce function to object");
    } else if constexpr (std::is_same_v<T, Array>) {
      throw std::runtime_error("Cannot coerce function to array");
    }
    throw std::runtime_error("Invalid coercion");
  }

  auto operator()(Object const& value) const -> T {
    if constexpr (std::is_same_v<T, int>) {
      throw std::runtime_error("Cannot coerce object to int");
    } else if constexpr (std::is_same_v<T, bool>) {
      return true;
    } else if constexpr (std::is_same_v<T, std::string>) {
      return "object";
    } else if constexpr (std::is_same_v<T, Function>) {
      throw std::runtime_error("Cannot coerce object to function");
    } else if constexpr (std::is_same_v<T, Object>) {
      return value;
    } else if constexpr (std::is_same_v<T, Array>) {
      throw std::runtime_error("Cannot coerce object to array");
    }
    throw std::runtime_error("Invalid coercion");
  }

  auto operator()(Array const& value) const -> T {
    if constexpr (std::is_same_v<T, int>) {
      throw std::runtime_error("Cannot coerce array to int");
    } else if constexpr (std::is_same_v<T, bool>) {
      return true;
    } else if constexpr (std::is_same_v<T, std::string>) {
      return "array";
    } else if constexpr (std::is_same_v<T, Function>) {
      throw std::runtime_error("Cannot coerce array to function");
    } else if constexpr (std::is_same_v<T, Object>) {
      throw std::runtime_error("Cannot coerce array to object");
    } else if constexpr (std::is_same_v<T, Array>) {
      return value;
    }
    throw std::runtime_error("Invalid coercion");
  }
};
}  // namespace ctjs
