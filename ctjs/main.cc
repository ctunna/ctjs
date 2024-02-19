#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#include "environment.h"
#include "parser.h"
#include "tokenizer.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  std::ifstream file(argv[1]);
  std::string code((std::istreambuf_iterator<char>(file)),
                   std::istreambuf_iterator<char>());
  ctjs::Parser p{code};
  auto program{p.parse()};
  program->to_string(0);

  std::cout << std::endl;

  auto env{std::make_shared<ctjs::Environment>()};
  program->evaluate(env);
  env->to_string();

  return 0;
}
