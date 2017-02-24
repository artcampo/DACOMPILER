#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "ErrorLog.hpp"
#include <map>
#include <memory>

namespace Compiler{

using AST::Node;

class LnessRness {
public:

  LnessRness(){}


  bool IsLValue(const Node& n) const{
    return node_is_lval_or_rval_.at(&n);
  }

  bool IsRValue(const Node& n) const{
    return not node_is_lval_or_rval_.at(&n);
  }

  void SetNodeAsLval(const Node& n) noexcept{
    node_is_lval_or_rval_[&n] = true;
  }

  void SetNodeAsRval(const Node& n) noexcept{
    node_is_lval_or_rval_[&n] = false;
  }

protected:
  std::map<const Node*,bool> node_is_lval_or_rval_;
};



}//end namespace Compiler
