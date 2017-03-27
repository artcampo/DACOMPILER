#pragma once
#include "AST/AST.hpp"
#include "Scopes/LexicalScope.hpp"
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
using AST::LexicalScope;

class TreeDecoration : public LnessRness{
public:
  TreeDecoration(){}

  bool IsRead(const ExprVar& n) const{return var_is_read_or_write_.at(&n);}
  bool IsWrite(const ExprVar& n) const{return not var_is_read_or_write_.at(&n);}

  bool IsValueAccess(const Var& n) const{return var_is_val_or_addr_.at(&n);}
  bool IsAddressAccess(const Var& n) const{return not var_is_val_or_addr_.at(&n);}

  bool IsMemberVar(const ExprVar& n) const{return var_is_member_.at(&n);}

  void SetAsRead(const ExprVar& n) noexcept{var_is_read_or_write_[&n] = true;}
  void SetAsWrite(const ExprVar& n) noexcept{var_is_read_or_write_[&n] = false;}

  void SetVarUsageAsValue(const Var& n) noexcept{var_is_val_or_addr_[&n] = true;}
  void SetVarUsageAsAddress(const Var& n) noexcept{var_is_val_or_addr_[&n] = false;}

  void SetIsMemberVar(const ExprVar& n, const bool is_member) noexcept{
    var_is_member_[&n] = is_member;
  }

  void SetTypeOfNode(const Node& n, const Type& t){
//     std::cout << "Set: " << n->str() << ": " << t.str() << "\n";
    type_of_node_[&n]=&t;
  }

  void SetLScopeOfNode(const Node& n, const LexicalScope& s){
//     std::cout << "Set: " << n->str() << ": " << t.str() << "\n";
    lscope_of_node_[&n]=&s;
  }  
  

  const Type& GetTypeOfNode(const Node& n){
//     std::cout << "Get: " << n->str() << ": " << type_of_node_[n]->str() << "\n";
    return *type_of_node_[&n];
  }
  
  const LexicalScope& GetLScopeOfNode(const Node& n){
//     std::cout << "Get: " << n->str() << ": " << type_of_node_[n]->str() << "\n";
    return *lscope_of_node_[&n];
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

  bool HasIsVarMember(const Node& n) const{
    auto it = var_is_member_.find(&n);
    return it != var_is_member_.end();
  }


  std::string ReadWriteStr(const Node& n) const{
    if(not HasReadWrite(n)) return "No ReadWrite";
    if(IsRead(dynamic_cast<const ExprVar&>(n)))  return "Read";
    if(IsWrite(dynamic_cast<const ExprVar&>(n))) return "Write";
  }

  std::string VarUsageStr(const Node& n) const{
    if(not HasVarUsage(n))  return "No VarUsage";
    if(IsValueAccess(dynamic_cast<const Var&>(n)))    return "Value";
    if(IsAddressAccess(dynamic_cast<const Var&>(n)))  return "Address";
  }

  std::string VarIsMemberStr(const Node& n) const{
    if(not HasIsVarMember(n)) return "No VarIsMember";
    if(IsMemberVar(dynamic_cast<const ExprVar&>(n))) return "Memb";
    else                                             return "Nmemb";
  }


protected:
//   std::map<const Node*,bool> node_is_lval_or_rval_;
  std::map<const Node*,bool> var_is_read_or_write_;
  std::map<const Node*,bool> var_is_val_or_addr_;
  std::map<const Node*,bool> var_is_member_;

  std::map<const Node*, const LexicalScope*>  lscope_of_node_;
  std::map<const Node*, const Type*>  type_of_node_;
  OffsetTable       module_offset_table_;

  OffsetTable& ModuleOffsetTable() noexcept{ return module_offset_table_;}
  const OffsetTable& ModuleOffsetTable() const noexcept{ return module_offset_table_;}
};



}//end namespace Compiler
