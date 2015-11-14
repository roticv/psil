#include <iostream>

#include "RpnParser.h"

int main() {
  while (1) {
    std::string input;
    std::cout << "psil-rpn> ";
    std::getline(std::cin, input);
    std::cout << "Your input is: " << input << std::endl;
    RpnParser parser(std::move(input));
    AST* ast = parser.parse();
    if (ast) {
      std::cout << ast->evaluate() << std::endl;
      delete ast;
    } else {
      std::cout << "Failed to parse input." << std::endl;
    }
  }
  return 0;
}
