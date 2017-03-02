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
using AST::Var;

class LnessRness {
public:
  LnessRness(){}

  bool IsLValue(const Node& n) const{return node_is_lval_or_rval_.at(&n);}
  bool IsRValue(const Node& n) const{return not node_is_lval_or_rval_.at(&n);}

  bool IsRead(const Var& n) const{return var_is_read_or_write_.at(&n);}
  bool IsWrite(const Var& n) const{return not var_is_read_or_write_.at(&n);}

  bool IsValueAccess(const Var& n) const{return var_is_val_or_addr_.at(&n);}
  bool IsAddressAccess(const Var& n) const{return not var_is_val_or_addr_.at(&n);}

  bool HasLRness(const Node& n) const{
    auto it = node_is_lval_or_rval_.find(&n);
    return it != node_is_lval_or_rval_.end();
  }

  std::string LRnessStr(const Node& n) const{
    if(not HasLRness(n))  return std::string("No LRness");
    if(IsLValue(n))       return std::string("Lvalue");
    if(IsRValue(n))       return std::string("Rvalue");
  }

  void SetNodeAsLval(const Node& n) noexcept{
    node_is_lval_or_rval_[&n] = true;
  }

  void SetNodeAsRval(const Node& n) noexcept{
    node_is_lval_or_rval_[&n] = false;
  }

  void SetVarAsRead(const Var& n) noexcept{
    var_is_read_or_write_[&n] = true;
  }

  void SetVarAsWrite(const Var& n) noexcept{
    var_is_read_or_write_[&n] = false;
  }

  void SetVarUsageAsValue(const Var& n) noexcept{
    var_is_val_or_addr_[&n] = true;
  }

  void SetVarUsageAsAddress(const Var& n) noexcept{
    var_is_val_or_addr_[&n] = false;
  }

protected:
  std::map<const Node*,bool> node_is_lval_or_rval_;
  std::map<const Node*,bool> var_is_read_or_write_;
  std::map<const Node*,bool> var_is_val_or_addr_;
};



}//end namespace Compiler
