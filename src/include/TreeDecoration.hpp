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
using AST::ExprVar;
using AST::OffsetTable;
using AST::OffsetTable;

class TreeDecoration : public LnessRness{
public:
  TreeDecoration(){}

  bool IsRead(const ExprVar& n) const{return var_is_read_or_write_.at(&n);}
  bool IsWrite(const ExprVar& n) const{return not var_is_read_or_write_.at(&n);}

  bool IsValueAccess(const Var& n) const{return var_is_val_or_addr_.at(&n);}
  bool IsAddressAccess(const Var& n) const{return not var_is_val_or_addr_.at(&n);}

  void SetAsRead(const ExprVar& n) noexcept{var_is_read_or_write_[&n] = true;}
  void SetAsWrite(const ExprVar& n) noexcept{var_is_read_or_write_[&n] = false;}

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

  bool HasReadWrite(const Node& n) const{
    auto it = var_is_read_or_write_.find(&n);
    return it != var_is_read_or_write_.end();
  }

  bool HasVarUsage(const Node& n) const{
    auto it = var_is_val_or_addr_.find(&n);
    return it != var_is_val_or_addr_.end();
  }


  std::string ReadWriteStr(const Node& n) const{
    if(not HasReadWrite(n)) return std::string("No ReadWrite");
    if(IsRead(dynamic_cast<const ExprVar&>(n)))  return std::string("Read");
    if(IsWrite(dynamic_cast<const ExprVar&>(n))) return std::string("Write");
  }

  std::string VarUsageStr(const Node& n) const{
    if(not HasVarUsage(n))  return std::string("No VarUsage");
    if(IsValueAccess(dynamic_cast<const Var&>(n)))    return std::string("Value");
    if(IsAddressAccess(dynamic_cast<const Var&>(n)))  return std::string("Address");
  }



protected:
//   std::map<const Node*,bool> node_is_lval_or_rval_;
  std::map<const Node*,bool> var_is_read_or_write_;
  std::map<const Node*,bool> var_is_val_or_addr_;

  std::map<const Node*, const Type*>  type_of_node_;
  OffsetTable       module_offset_table_;

  OffsetTable& ModuleOffsetTable() noexcept{ return module_offset_table_;}
  const OffsetTable& ModuleOffsetTable() const noexcept{ return module_offset_table_;}
};



}//end namespace Compiler
