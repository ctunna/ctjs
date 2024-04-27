#include <filesystem>
#include <string>
#include <vector>

#include "ctjs/interpreter.h"

auto main() -> int {
  ctjs::Interpreter interpreter;
  std::vector<std::string> includes{{"tests/js/lib"}, {"tests/js/tests"}};
  for (const auto& include : includes) {
    for (const auto& path : std::filesystem::directory_iterator(include)) {
      interpreter.eval_file(path.path());
    }
  }
  return 0;
}
