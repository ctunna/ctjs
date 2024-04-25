#pragma once

#include <memory>
#include <string_view>

#include "ctjs/runtime/environment.h"

namespace ctjs {
class Interpreter {
 public:
  Interpreter();

  void eval(std::string file_name, std::string_view code);
  void eval(std::string_view code);
  void eval_file(const std::string& file_name);

 private:
  std::shared_ptr<Environment> globals_{std::make_shared<Environment>()};
  std::shared_ptr<Environment> environment_{std::make_shared<Environment>(globals_)};
};
}  // namespace ctjs
