#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "ErrorLog.hpp"
#include "LnessRness.hpp"
#include "Function.hpp"
#include <map>
#include <memory>

namespace Compiler{

using AST::Node;
using AST::Var;
using AST::OffsetTable;
using AST::OffsetTable;

class TreeDecoration : public LnessRness{
public:
  TreeDecoration(){}

  bool IsRead(const Var& n) const{return var_is_read_or_write_.at(&n);}
  bool IsWrite(const Var& n) const{return not var_is_read_or_write_.at(&n);}

  bool IsValueAccess(const Var& n) const{return var_is_val_or_addr_.at(&n);}
  bool IsAddressAccess(const Var& n) const{return not var_is_val_or_addr_.at(&n);}

  void SetVarAsRead(const Var& n) noexcept{var_is_read_or_write_[&n] = true;}
  void SetVarAsWrite(const Var& n) noexcept{var_is_read_or_write_[&n] = false;}

  void SetVarUsageAsValue(const Var& n) noexcept{var_is_val_or_addr_[&n] = true;}
  void SetVarUsageAsAddress(const Var& n) noexcept{var_is_val_or_addr_[&n] = false;}

  void SetTypeOfNode(const Node& n, const Type& t){
//     std::cout << "Set: " << n->str() << ": " << t.str() << "\n";
    type_of_node_[&n]=&t;
  }

  const Type& GetTypeOfNode(const Node& n){
//     std::cout << "Get: " << n->str() << ": " << type_of_node_[n]->str() << "\n";
    return *type_of_node_[&n];
  }

  IR::Offset LocalVarOffset(const Var& n) const{
    return module_offset_table_.at(n.Id());
  }



protected:
  std::map<const Node*,bool> node_is_lval_or_rval_;
  std::map<const Node*,bool> var_is_read_or_write_;
  std::map<const Node*,bool> var_is_val_or_addr_;

  std::map<const Node*, const Type*>  type_of_node_;
  OffsetTable       module_offset_table_;

  OffsetTable& ModuleOffsetTable() noexcept{ return module_offset_table_;}
  const OffsetTable& ModuleOffsetTable() const noexcept{ return module_offset_table_;}
};



}//end namespace Compiler
