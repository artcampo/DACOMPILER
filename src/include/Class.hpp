#pragma once
#include "Types.hpp"
#include "Symbol.hpp"
#include "AST/AST.hpp"
#include "AST/Node.hpp"
#include "IR/Label.hpp"
#include "IR/Offset.hpp"
#include "Module/TypeTable.hpp"
#include "Scopes/Scope.hpp"
#include "Scopes/ScopeId.hpp"
#include "Scopes/HierarchicalScope.hpp"
#include <map>
#include <memory>

namespace Compiler{
namespace AST{

using AST::Ast;
using AST::Type;
using AST::Node;
using AST::ScopeId;
using AST::HierarchicalScope;
using namespace Compiler::AST::Ptrs;
using IR::Label;
using IR::Offset;

class Class;
using PtrClass = std::unique_ptr<Class>;



class Class{
public:

  Class(const std::string& name
    , const ScopeOwnerId scope_owner_id
    , const ScopeId scope_id
    , HierarchicalScope& scope
    , const IR::Label this_label)
  : name_(name)
    , scope_owner_id_(scope_owner_id)
    , scope_(scope)
    , this_label_(this_label){}

  HierarchicalScope& GetHScope() const noexcept{ return scope_;}

  const IR::Label ThisLabel() const noexcept{ return this_label_; }
  const IR::Offset MemberVarOffset(AST::Symbols::SymbolId& sid) const noexcept{
    return Offset(0, "test");
  }

  std::string str()  const noexcept{ return name_;}
private:
  ScopeOwnerId          scope_owner_id_;
  std::string           name_;
  HierarchicalScope&    scope_;
  IR::Label             this_label_;

  /*
  Symbols::Symbol& GetSymbolDecl(const Node& n) const{
//     std::cout << "Asking n: " << &n << " " << n.str() << std::endl;
    return *symbol_decl_of_node_.at(&n);
  }

  void StoreDecl(Symbols::Symbol& s, const Node& n){
    symbol_decl_of_node_[&n] = &s;
  }
  */

/*
  void SetOriginNode(const FuncDef& n){
    origin_node_ = const_cast<FuncDef*>(&n);
  }
  */

};


}//end namespace AST
}//end namespace Compiler
