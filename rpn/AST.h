#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

enum class ASTType {
  OP,
  NUMBER
};

namespace {

std::ostream& operator<<(std::ostream& os, ASTType type) {
  switch (type) {
    case ASTType::OP:
      os << "OP";
      break;
    case ASTType::NUMBER:
      os << "NUMBER";
      break;
    default:
      os << "Unknown ASTType";
  }
  return os;
}

}

class AST {
 public:
  ~AST() {
    for (int i = 0; i < children_.size(); ++i) {
      delete children_[i];
    }
  }

  ASTType getType() {
    return type_;
  }

  const std::string& getValue() {
    return content_;
  }

  const std::vector<AST*>& getChildren() {
    return children_;
  }

  void addChild(AST* child) {
    children_.push_back(child);
  }

  void print() {
    std::cout << "(type: " << type_ << ", content: " << content_
              << ", children: [" << std::endl;
    for (auto child : children_) {
      child->print();
    }
    std::cout << "]" << std::endl;
  }

  int64_t evaluate() {
    return AST::evaluate(this);
  }

  static int64_t evaluate(AST* ast) {
    if (ast->getType() == ASTType::OP) {
      int64_t res = 0;
      const auto& children = ast->getChildren();
      char op = ast->getValue().front();
      for (int i = 0; i < children.size(); ++i) {
        if (i == 0) {
          res = children[i]->evaluate();
          continue;
        }
        switch (op) {
          case '+':
            res += children[i]->evaluate();
            break;
          case '-':
            res -= children[i]->evaluate();
            break;
          case '*':
            res *= children[i]->evaluate();
            break;
          case '/':
            res /= children[i]->evaluate();
            break;
        }
      }
      return res;
    } else if (ast->getType() == ASTType::NUMBER) {
      return std::stoll(ast->getValue());
    } else {
      assert(false);
    }
  }

  static AST* makeOperatorAST(char op) {
    std::string content;
    content.push_back(op);
    return new AST(ASTType::OP, std::move(content));
  }

  static AST* makeNumberAST(std::string content) {
    return new AST(ASTType::NUMBER, std::move(content));
  }

 private:
  AST(ASTType type, std::string content)
    : type_(type),
      content_(std::move(content)) {}

  ASTType type_;
  std::string content_;

  std::vector<AST*> children_;
};
