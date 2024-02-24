#include "ctjs/runtime/value.h"

namespace ctjs {
struct PlusVisitor {
  auto operator()(int a, int b) const -> Value { return a + b; }
  auto operator()(int a, bool b) const -> Value { return a + b; }
  auto operator()(bool a, int b) const -> Value { return a + b; }
  auto operator()(bool a, bool b) const -> Value { return a + b; }
  auto operator()([[maybe_unused]] int a, [[maybe_unused]] Function b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] int b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] bool a, [[maybe_unused]] Function b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] bool b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] Function b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()(int a, std::string b) const -> Value {
    return std::to_string(a) + b;
  }
  auto operator()(std::string a, int b) const -> Value {
    return a + std::to_string(b);
  }
  auto operator()(bool a, std::string b) const -> Value {
    return (a ? "true" : "false") + b;
  }
  auto operator()(std::string a, bool b) const -> Value {
    return a + (b ? "true" : "false");
  }
  auto operator()(std::string a, std::string b) const -> Value { return a + b; }
  auto operator()([[maybe_unused]] std::string a,
                  [[maybe_unused]] Function b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] std::string b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
};

struct MinusVisitor {
  auto operator()(int a, int b) const -> Value { return a - b; }
  auto operator()(int a, bool b) const -> Value { return a - b; }
  auto operator()(bool a, int b) const -> Value { return a - b; }
  auto operator()(bool a, bool b) const -> Value { return a - b; }
  auto operator()([[maybe_unused]] int a, [[maybe_unused]] Function b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] int b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] bool a, [[maybe_unused]] Function b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] bool b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] Function b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] int a, [[maybe_unused]] std::string b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a, [[maybe_unused]] int b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] bool a, [[maybe_unused]] std::string b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a, [[maybe_unused]] bool b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a,
                  [[maybe_unused]] std::string b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a,
                  [[maybe_unused]] Function b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] std::string b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
};

struct MulVisitor {
  auto operator()(int a, int b) const -> Value { return a * b; }
  auto operator()(int a, bool b) const -> Value { return a * b; }
  auto operator()(bool a, int b) const -> Value { return a * b; }
  auto operator()(bool a, bool b) const -> Value { return a * b; }
  auto operator()([[maybe_unused]] int a, [[maybe_unused]] Function b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] int b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] bool a, [[maybe_unused]] Function b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] bool b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] Function b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] int a, [[maybe_unused]] std::string b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a, [[maybe_unused]] int b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] bool a, [[maybe_unused]] std::string b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a, [[maybe_unused]] bool b) const
      -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a,
                  [[maybe_unused]] std::string b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a,
                  [[maybe_unused]] Function b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] std::string b) const -> Value {
    throw std::runtime_error{"Unsupported operation"};
  }
};

struct GreaterThanVisitor {
  auto operator()(int a, int b) const -> bool { return a > b; }
  auto operator()(int a, bool b) const -> bool { return a > b; }
  auto operator()(bool a, int b) const -> bool { return a > b; }
  auto operator()(bool a, bool b) const -> bool { return a > b; }
  auto operator()([[maybe_unused]] int a, [[maybe_unused]] Function b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] int b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] bool a, [[maybe_unused]] Function b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] bool b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] Function b) const -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] int a, [[maybe_unused]] std::string b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a, [[maybe_unused]] int b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] bool a, [[maybe_unused]] std::string b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a, [[maybe_unused]] bool b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a,
                  [[maybe_unused]] std::string b) const -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a,
                  [[maybe_unused]] Function b) const -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] std::string b) const -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
};

struct EqualsVisitor {
  auto operator()(int a, int b) const -> bool { return a == b; }
  auto operator()(int a, bool b) const -> bool { return a == b; }
  auto operator()(bool a, int b) const -> bool { return a == b; }
  auto operator()(bool a, bool b) const -> bool { return a == b; }
  auto operator()([[maybe_unused]] int a, [[maybe_unused]] Function b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] int b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] bool a, [[maybe_unused]] Function b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a, [[maybe_unused]] bool b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] Function b) const -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] int a, [[maybe_unused]] std::string b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a, [[maybe_unused]] int b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] bool a, [[maybe_unused]] std::string b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a, [[maybe_unused]] bool b) const
      -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a,
                  [[maybe_unused]] std::string b) const -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] std::string a,
                  [[maybe_unused]] Function b) const -> bool {
    throw std::runtime_error{"Unsupported operation"};
  }
  auto operator()([[maybe_unused]] Function a,
                  [[maybe_unused]] std::string b) const -> bool {
    throw std::runtime_error{"Unsupported operation"};
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
  return std::visit(PlusVisitor{}, value_, other.value_);
}

auto Value::operator-(const Value& other) const -> Value {
  return std::visit(MinusVisitor{}, value_, other.value_);
}

auto Value::operator*(const Value& other) const -> Value {
  return std::visit(MulVisitor{}, value_, other.value_);
}

auto Value::operator>(const Value& other) const -> bool {
  return std::visit(GreaterThanVisitor{}, value_, other.value_);
}

auto Value::operator<(const Value& other) const -> bool {
  return !(*this > other) && !(*this == other);
}

auto Value::operator==(const Value& other) const -> bool {
  return std::visit(EqualsVisitor{}, value_, other.value_);
}

auto Value::to_string() const -> std::string {
  return std::visit(ToStringVisitor{}, value_);
}
}  // namespace ctjs
