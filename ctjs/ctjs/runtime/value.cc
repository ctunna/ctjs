#include "ctjs/runtime/value.h"

#include "ctjs/runtime/coerce.h"

namespace ctjs {
template <typename T, typename U>
concept HasPlusOperator = requires(T lhs, U rhs) {
  { lhs + rhs } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept HasMinusOperator = requires(T lhs, U rhs) {
  { lhs - rhs } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept HasMultiplyOperator = requires(T lhs, U rhs) {
  { lhs* rhs } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept HasDivisionOperator = requires(T lhs, U rhs) {
  { lhs / rhs } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept HasGreaterThanOperator = requires(T lhs, U rhs) {
  { lhs > rhs } -> std::convertible_to<bool>;
};

template <typename T, typename U>
concept HasEqualsOperator = requires(T lhs, U rhs) {
  { lhs == rhs } -> std::convertible_to<bool>;
};

struct PlusVisitor {
  auto operator()(auto const& lhs, auto const& rhs) const -> Value {
    using R = std::decay_t<decltype(lhs)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasPlusOperator<decltype(lhs), decltype(coerce(rhs))>) {
      return Value(lhs + coerce(rhs));
    }
    throw std::runtime_error("Invalid lhsddition");
  }
  auto operator()(auto const& lhs, std::string const& rhs) const -> Value {
    auto coerce{Coerce<std::string>{}};
    return Value(coerce(lhs) + rhs);
  }
};

struct MinusVisitor {
  auto operator()(auto const& lhs, auto const& rhs) const -> Value {
    using R = std::decay_t<decltype(lhs)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasMinusOperator<decltype(lhs), decltype(coerce(rhs))>) {
      return Value(lhs - coerce(rhs));
    }
    throw std::runtime_error("Invalid subtraction");
  }
};

struct MultiplyVisitor {
  auto operator()(auto const& lhs, auto const& rhs) const -> Value {
    using R = std::decay_t<decltype(lhs)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasMultiplyOperator<decltype(lhs), decltype(coerce(rhs))>) {
      return Value(lhs * coerce(rhs));
    }
    throw std::runtime_error("Invalid multiplication");
  }
};

struct DivisionVisitor {
  auto operator()(auto const& lhs, auto const& rhs) const -> Value {
    using R = std::decay_t<decltype(lhs)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasDivisionOperator<decltype(lhs), decltype(coerce(rhs))>) {
      return Value(lhs / coerce(rhs));
    }
    throw std::runtime_error("Invalid multiplication");
  }
};

struct GreaterThanVisitor {
  auto operator()(auto const& lhs, auto const& rhs) const -> bool {
    using R = std::decay_t<decltype(lhs)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasGreaterThanOperator<decltype(lhs),
                                         decltype(coerce(rhs))>) {
      return lhs > coerce(rhs);
    }
    throw std::runtime_error("Invalid comparison");
  }
};

struct EqualsVisitor {
  auto operator()(auto const& lhs, auto const& rhs) const -> bool {
    using R = std::decay_t<decltype(lhs)>;
    auto coerce{Coerce<R>{}};
    if constexpr (HasEqualsOperator<decltype(lhs), decltype(coerce(rhs))>) {
      return lhs == coerce(rhs);
    }
    throw std::runtime_error("Invalid comparison");
  }
};

struct IndexVisitor {
  auto operator()(std::shared_ptr<Object>& lhs, std::string const& rhs) const
      -> Value {
    return lhs->get_property(rhs);
  }
  auto operator()(std::shared_ptr<Object>& lhs, int const& rhs) const -> Value {
    return lhs->get_property(std::to_string(rhs));
  }
  auto operator()([[maybe_unused]] auto& lhs, [[maybe_unused]] auto& rhs) const
      -> Value {
    throw std::runtime_error("Invalid index operation");
  }
};

struct IterableVisitor {
  auto operator()(std::shared_ptr<Object>& value) const
      -> std::map<std::string, Value> {
    return value->properties();
  }
  auto operator()([[maybe_unused]] auto& value) const
      -> std::map<std::string, Value> {
    throw std::runtime_error("Invalid iterable");
  }
};

struct ToStringVisitor {
  auto operator()(int const& value) const -> std::string {
    return std::to_string(value);
  }
  auto operator()(bool const& value) const -> std::string {
    return value ? "true" : "false";
  }
  auto operator()(std::string const& value) const -> std::string {
    return value;
  }
  auto operator()(std::shared_ptr<Object> const& value) const -> std::string {
    return value->to_string();
  }
};

Value::Value(int value) : value_(value) {}
Value::Value(bool value) : value_(value) {}
Value::Value(std::string value) : value_(value) {}
Value::Value(std::shared_ptr<Object> value) : value_(std::move(value)) {}

auto Value::operator+(Value const& other) const -> Value {
  static auto visitor{PlusVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator-(Value const& other) const -> Value {
  static auto visitor{MinusVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator*(Value const& other) const -> Value {
  static auto visitor{MultiplyVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator/(Value const& other) const -> Value {
  static auto visitor{DivisionVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator>(Value const& other) const -> bool {
  static auto visitor{GreaterThanVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator<(Value const& other) const -> bool {
  return !(*this > other) && !(*this == other);
}

auto Value::operator==(Value const& other) const -> bool {
  static auto visitor{EqualsVisitor{}};
  return std::visit(visitor, value_, other.value_);
}

auto Value::operator[](Value const& other) -> Value {
  static auto visitor{IndexVisitor{}};
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
