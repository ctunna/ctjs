#include "ctjs/runtime/value.h"

#include "ctjs/runtime/coerce.h"

namespace ctjs {
template <typename T, typename U>
concept HasPlusOperator = requires(T a, U b) {
  { a + b } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept HasMinusOperator = requires(T a, U b) {
  { a - b } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept HasMultiplyOperator = requires(T a, U b) {
  { a* b } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept HasGreaterThanOperator = requires(T a, U b) {
  { a > b } -> std::convertible_to<bool>;
};

template <typename T, typename U>
concept HasEqualsOperator = requires(T a, U b) {
  { a == b } -> std::convertible_to<bool>;
};

struct PlusVisitor {
  auto operator()(auto const& a, auto const& b) const -> Value {
    using R = std::decay_t<decltype(a)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasPlusOperator<decltype(a), decltype(coerce(b))>) {
      return a + coerce(b);
    }
    throw std::runtime_error("Invalid addition");
  }
  auto operator()(auto const& a, std::string const& b) const -> Value {
    auto coerce{Coerce<std::string>{}};
    return coerce(a) + b;
  }
};

struct MinusVisitor {
  auto operator()(auto const& a, auto const& b) const -> Value {
    using R = std::decay_t<decltype(a)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasMinusOperator<decltype(a), decltype(coerce(b))>) {
      return a - coerce(b);
    }
    throw std::runtime_error("Invalid subtraction");
  }
};

struct MultiplyVisitor {
  auto operator()(auto const& a, auto const& b) const -> Value {
    using R = std::decay_t<decltype(a)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasMultiplyOperator<decltype(a), decltype(coerce(b))>) {
      return a * coerce(b);
    }
    throw std::runtime_error("Invalid multiplication");
  }
};

struct GreaterThanVisitor {
  auto operator()(auto const& a, auto const& b) const -> bool {
    using R = std::decay_t<decltype(a)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasGreaterThanOperator<decltype(a), decltype(coerce(b))>) {
      return a > coerce(b);
    }
    throw std::runtime_error("Invalid comparison");
  }
};

struct EqualsVisitor {
  auto operator()(auto const& a, auto const& b) const -> bool {
    using R = std::decay_t<decltype(a)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasEqualsOperator<decltype(a), decltype(coerce(b))>) {
      return a == coerce(b);
    }
    throw std::runtime_error("Invalid comparison");
  }
};

struct ToStringVisitor {
  auto operator()(int value) const -> std::string {
    return std::to_string(value);
  }
  auto operator()(bool value) const -> std::string {
    return value ? "true" : "false";
  }
  auto operator()([[maybe_unused]] Function value) const -> std::string {
    return "function()";
  }
  auto operator()(std::string value) const -> std::string { return value; }
};

Value::Value(int value) : value_(value) {}
Value::Value(bool value) : value_(value) {}
Value::Value(Function value) : value_(value) {}
Value::Value(std::string value) : value_(value) {}

auto Value::operator+(const Value& other) const -> Value {
  static auto visitor{PlusVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator-(const Value& other) const -> Value {
  static auto visitor{MinusVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator*(const Value& other) const -> Value {
  static auto visitor{MultiplyVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator>(const Value& other) const -> bool {
  static auto visitor{GreaterThanVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator<(const Value& other) const -> bool {
  return !(*this > other) && !(*this == other);
}

auto Value::operator==(const Value& other) const -> bool {
  static auto visitor{EqualsVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

Value::operator bool() const {
  static auto coerce{Coerce<bool>{}};
  return std::visit(coerce, value_);
}

auto Value::to_string() const -> std::string {
  static auto visitor{ToStringVisitor{}};
  return std::visit(visitor, value_);
}
}  // namespace ctjs
