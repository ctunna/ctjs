#include "ctjs/runtime/builtin.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include "ctjs/runtime/value.h"

namespace ctjs {
auto MakeAssert() -> Value {
  auto assert{
      std::make_shared<Builtin::Function>([](const std::vector<Value>& args) {
        if (!args.empty()) {
          assert(args[0]);
        }
        return Value();
      })};
  return Value(assert);
}

auto MakeConsole() -> Value {
  auto console{std::make_shared<Object>()};
  auto log{
      std::make_shared<Builtin::Function>([](const std::vector<Value>& args) {
        for (const auto& arg : args) {
          std::cout << arg.to_string() << ' ';
        }
        std::cout << '\n';
        return Value();
      })};
  console->set_property("log", Value(log));
  return Value(console);
}

void Builtin::apply(const std::shared_ptr<Environment>& environment) {
  environment->define("console", MakeConsole());
  environment->define("assert", MakeAssert());
}

Builtin::Function::Function(std::function<Value(std::vector<Value>)> func)
    : func_(std::move(func)) {}

auto Builtin::Function::call(std::vector<Value> args) -> Value {
  return func_(args);
}
}  // namespace ctjs