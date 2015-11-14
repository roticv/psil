#include "RpnParser.h"

RpnParser::RpnParser(std::string input)
  : data_(std::move(input)) {
}

AST* RpnParser::parse() {
  idx_ = 0;
  return parseExpression();
}

AST* RpnParser::parseOperator() {
  if (idx_ >= data_.size()) {
    return nullptr;
  }
  AST* result = nullptr;
  switch (data_[idx_]) {
    case '-':
    case '+':
    case '/':
    case '*':
      result = AST::makeOperatorAST(data_[idx_++]); // tricky usage of idx_++
      skipSpaces();
      return result;
    default:
      return nullptr;
  }
}

AST* RpnParser::parseNumber() {
  if (idx_ >= data_.size()) {
    return nullptr;
  }
  int oldIdx = idx_;
  while (idx_ < data_.size()) {
    if (data_[idx_] < '0' || data_[idx_] > '9') {
      break;
    }
    ++idx_;
  }
  if (oldIdx == idx_) {
    // No [0-9] matched
    return nullptr;
  }
  skipSpaces();
  return AST::makeNumberAST(data_.substr(oldIdx, idx_ - oldIdx));
}

AST* RpnParser::parseExpression() {
  AST* numAST = parseNumber();
  if (numAST) {
    return numAST;
  }
  // '(' <symbol> <expr>+ ')' variant
  if (idx_ >= data_.size()) {
    return nullptr;
  }
  if (data_[idx_] != '(') {
    return nullptr;
  }
  int oldIdx = idx_;
  ++idx_;
  skipSpaces();
  AST* opAST = parseOperator();
  if (opAST == nullptr) {
    // rollback idx_
    idx_ = oldIdx;
    return nullptr;
  }
  // TODO potential memory leak here since opAST may not be freed
  // in the case parseExpression is not even true the first time round
  AST* expr;
  while ((expr = parseExpression()) != nullptr) {
    opAST->addChild(expr);
  }
  if (data_[idx_] != ')') {
    return nullptr;
  }
  ++idx_;
  skipSpaces();
  return opAST;
}

void RpnParser::skipSpaces() {
  while (idx_ < data_.size() && data_[idx_] == ' ') {
    ++idx_;
  }
}
