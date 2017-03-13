#pragma once
#include "Types.hpp"
#include "Symbol.hpp"
#include "AST/AST.hpp"
#include "AST/Node.hpp"
#include "Module/TypeTable.hpp"
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
using namespace Compiler::AST::Ptrs;
using IR::Label;

class Class;
using PtrClass = std::unique_ptr<Class>;



class Class{
public:

  Class(const std::string& name
    , const ScopeOwnerId scope_owner_id
    , const ScopeId scope_id)
  : name_(name)
    , scope_owner_id_(scope_owner_id)
    , scope_(std::move(
      std::make_unique<HierarchicalScope>(scope_id, scope_owner_id, name))){}


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
  HierarchicalScope& GetScope() const noexcept{ return *scope_;}

  std::string str()  const noexcept{ return name_;}
private:
  ScopeOwnerId          scope_owner_id_;
  std::string           name_;
  PtrHierarchicalScope  scope_;


};


}//end namespace AST
}//end namespace Compiler
