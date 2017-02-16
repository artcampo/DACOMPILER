#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"
#include "Types.hpp"
#include <map>

namespace Compiler{

using AST::Ast;
using AST::LexicalScope;
using AST::TypeId;
using AST::Node;

class CompilationUnit {
public:

  CompilationUnit(): ast_(), scope_(nullptr){}

  const bool ValidAst() const noexcept { return ast_.block_ != nullptr; }

  Ast            ast_;
  LexicalScope*  scope_;

  void RecordType(const Node* n, const TypeId& t){
    type_info_[n]=t;
  }
  TypeId GetTypeId(const Node* n){
    return type_info_[n];
  }

  void Error(const std::string& e){
    std::cout << e << "\n";
  }
private:
  std::map<const Node*,TypeId> type_info_;
};


}//end namespace Compiler
