#pragma once

#include <string>

#include "AST.h"

/**
 * rpn language
 *
 * <operator> := '-' | '+' | '/' | '*'
 * <num>      := [0-9]+
 * <expr>     := <num> | '(' <symbol> <expr>+ ')'
 */

class RpnParser {
 public:
  RpnParser(std::string input);
  AST* parse();

 private:
  AST* parseOperator();
  AST* parseNumber();
  AST* parseExpression();
  void skipSpaces();

  std::string data_;
  int idx_;
};
