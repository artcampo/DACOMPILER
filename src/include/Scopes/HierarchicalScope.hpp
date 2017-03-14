#pragma once
#include "Scopes/Scope.hpp"

namespace Compiler{
namespace AST{

class HierarchicalScope : public Scope{
public:
  HierarchicalScope(const ScopeId id, const ScopeOwnerId scope_owner_id
    , const std::string& name_owner)
  : Scope(id, scope_owner_id), name_("HScope of " + name_owner){}

  ~HierarchicalScope() = default;

  bool RegisterDecl(const std::string& name, const Type& type
    ,  const Node& n, AST::Symbols::SymbolId symbol_id){
    auto it = symbol_table_.find(name);
    Symbols::SymbolId previous_id = -1;
    if(it != symbol_table_.end()){
      previous_id = it->second;
      if(declaration_table_[previous_id]->GetScopeId() == GetScopeId())
        return false;
    }
    symbol_table_[name] = symbol_id;
    declaration_table_[symbol_id] = std::make_unique<Symbols::Symbol>
                              (name, type, GetScopeId(), symbol_id);
//     symbolid_of_node_[&n] = symbol_id;
    return true;
  }

  bool IsDeclValid(const std::string& name){
    auto it = symbol_table_.find(name);
    Symbols::SymbolId previous_id = -1;
    if(it != symbol_table_.end()){
      previous_id = it->second;
      if(declaration_table_[previous_id]->GetScopeId() == GetScopeId())
        return false;
    }
    return true;
  }

  bool HasDecl(const std::string& name){
    auto it = symbol_table_.find(name);
    if(it == symbol_table_.end()) return false;
    return true;
  }

  const Symbols::SymbolId DeclId(const std::string& name) const{
    auto it = symbol_table_.find(name);
    return it->second;
  }

  const Type& GetType(const std::string& name) const{
    const Symbols::SymbolId sid = DeclId(name);
    return declaration_table_.at(sid)->GetType();
  }

  std::string str() const noexcept{
    std::string s = name_ + " "+  std::to_string(id_) + (": {");
    for(const auto& it : declaration_table_){
      s+= "(" + std::to_string(it.first) + ":";
      s+= it.second->BareName()+ ") ";
    }
    s += "}";
    return s;
  }

private:
  std::string       name_;
  SymbolTable       symbol_table_;
  DeclarationTable  declaration_table_;
//   SymbolIdOfNode    symbolid_of_node_;
};


}//end namespace AST
}//end namespace Compiler
