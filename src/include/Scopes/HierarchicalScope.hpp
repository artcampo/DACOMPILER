#pragma once
#include "Scopes/Scope.hpp"

namespace Compiler{
namespace AST{
  

class HierarchicalScope : public Scope{
public:
  HierarchicalScope(const ScopeId id, const ScopeOwnerId scope_owner_id
    , const std::string& name_owner
    , std::vector<HierarchicalScope*>& parent_scopes)
  : Scope(id, scope_owner_id), name_("HScope of " + name_owner)
    , parents_(parent_scopes){}

  ~HierarchicalScope() = default;

  bool RegisterDecl(const std::string& name, const Type& type
    ,  const Node& n, AST::Symbols::SymbolId symbol_id){
    //RegisterDecl only can insert in the current HScope
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
    auto it = Find(name);
    Symbols::SymbolId previous_id = -1;
    if(not IsLast(it)){
      previous_id = it->second;
      if(declaration_table_[previous_id]->GetScopeId() == GetScopeId())
        return false;
    }
    return true;
  }

  bool HasDecl(const std::string& name){
    auto it = Find(name);
    return not IsLast(it);
  }

  const Symbols::SymbolId DeclId(const std::string& name) const{
    auto it = Find(name);
    return it->second;
  }

  virtual const Type& GetType(const std::string& name) const override{
    const DeclarationTable* declaration_table;
    auto it = Find(name, &declaration_table);
    const Symbols::SymbolId sid = it->second;
    return declaration_table->at(sid)->GetType();
  }
  
  SymbolTableItC Find(const std::string& name)const{
    const DeclarationTable* d;  //won't be used
    return Find(name, &d);
  }

  SymbolTableItC Find(const std::string& name, const DeclarationTable** dec) const{
    auto it = symbol_table_.find(name);
    if(not IsLast(it)) { *dec = &declaration_table_; return it;} 
    
    //check parents
    for(auto& parent : parents_){
      auto itp = parent->Find(name);
      if(not parent->IsLast(itp)) {*dec = &parent->declaration_table_; return itp;}
    }    
    
    //not found, return it to last element within this hscope
    return it;
  }
  
  bool IsLast(SymbolTableItC& it) const{
    return it == symbol_table_.end();
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
  std::vector<HierarchicalScope*> parents_;
//   SymbolIdOfNode    symbolid_of_node_;
};


}//end namespace AST
}//end namespace Compiler
