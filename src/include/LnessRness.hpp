#pragma once
#include "AST/AST.hpp"
#include "AST/ASTNodes.hpp"
#include "LexicalScope.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "ErrorLog.hpp"
#include <map>
#include <memory>

namespace Compiler{

using AST::Node;
using AST::Var;

class LnessRness {
public:
  LnessRness(){}

  bool IsLValue(const Node& n) const{return node_is_lval_or_rval_.at(&n);}
  bool IsRValue(const Node& n) const{return not node_is_lval_or_rval_.at(&n);}


  bool HasLRness(const Node& n) const{
    auto it = node_is_lval_or_rval_.find(&n);
    return it != node_is_lval_or_rval_.end();
  }

  std::string LRnessStr(const Node& n) const{
    if(not HasLRness(n))  return std::string("No LRness");
    if(IsLValue(n))       return std::string("Lvalue");
    if(IsRValue(n))       return std::string("Rvalue");
  }

  void SetNodeAsLval(const Node& n) noexcept{node_is_lval_or_rval_[&n] = true;}
  void SetNodeAsRval(const Node& n) noexcept{node_is_lval_or_rval_[&n] = false;}

protected:
  std::map<const Node*,bool> node_is_lval_or_rval_;

};



}//end namespace Compiler
