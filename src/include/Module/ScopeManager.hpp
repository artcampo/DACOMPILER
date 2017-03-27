#pragma once
#include "Symbol.hpp"
#include "Types/TypeId.hpp"
#include "IR/Label.hpp"
#include "Scopes/Scope.hpp"
#include "Scopes/ScopeId.hpp"
#include "Scopes/LexicalScope.hpp"
#include "Scopes/HierarchicalScope.hpp"
#include <map>

namespace Compiler{

using AST::ScopeId;
using AST::Scope;
using AST::SymbolIdOfNode;
using AST::ScopeOwnerId;
using AST::PtrLexicalScope;
using AST::LexicalScope;
using AST::PtrHierarchicalScope;
using AST::HierarchicalScope;
using AST::TypeId;
using AST::SymbolTable;
using AST::DeclarationTable;

class ScopeManager{
public:
  ScopeManager() : free_scope_id_(0)
  , free_scope_ownner_id_(0)
  , global_scope_ownner_id_(0){}

  const ScopeOwnerId NewScopeOwner() noexcept{ return FreeScopeOwnerId(); }
  const ScopeOwnerId GlobalScopeOwnerId() const noexcept{ return global_scope_ownner_id_; }

  bool IsDeclValid(const std::string& name, const ScopeId scope_id){
    return GetScope(scope_id)->IsDeclValid(name);
  }

  bool HasDecl(const std::string& name, const ScopeId scope_id){
    return GetScope(scope_id)->HasDecl(name);

  }

  const AST::Symbols::SymbolId DeclId(const std::string& name
    , const ScopeId scope_id) const{
    return GetScope(scope_id)->DeclId(name);
  }

  const ScopeId NewHierarchicalScope(const std::string& class_name
    , const ScopeOwnerId scope_owner_id
    , const Type& class_type
    , std::vector<HierarchicalScope*>& parent_scopes){
    const ScopeId id = FreeScopeId();
    hier_scopes_.push_back( std::move(
      std::make_unique<HierarchicalScope>(id, scope_owner_id, class_name, parent_scopes) ));
    scope_by_id_[id] = hier_scopes_.back().get();
//     scope_is_lexical_or_hierarchical_[id] = false;
    hscope_by_class_typeid_[class_type.GetTypeId()] = id;
    hscope_by_class_name_[class_name] = id;
    return id;
  }

  PtrLexicalScope GlobalLexicalScope(SymbolTable& symbol_table
    , DeclarationTable& declaration_table
    , SymbolIdOfNode& symbolid_of_node){
    const ScopeId id = FreeScopeId();
    PtrLexicalScope g = std::make_unique<LexicalScope>(
        id, nullptr, FreeScopeOwnerId(), symbol_table
        , declaration_table, symbolid_of_node);
    scope_by_id_[id] = g.get();
    current_scope_ = g.get();
    global_scope_id_ = id;
    return std::move(g);
  }

  const ScopeId NewNestedScope(const ScopeOwnerId scope_owner_id){
    const ScopeId id = FreeScopeId();
    LexicalScope* new_scope;
    new_scope = current_scope_->NewNestedScope(id, scope_owner_id);
    scope_by_id_[id] = new_scope;
//     scope_is_lexical_or_hierarchical_[id] = true;
    current_scope_   = new_scope;
    return id;
  }

  void RestoreScope(){
//     std::cout << "*** restoring: " << current_scope_->str()<< "\n";
    current_scope_->UndoTables();
    current_scope_ = current_scope_->GetParentScope();
//     std::cout << "*** to: " << current_scope_->str()<< "\n";
  }

  bool ScopeIsLexical(const ScopeId id) const{
//     std::cout << "asking: " << id<<std::endl;
    return scope_is_lexical_or_hierarchical_.at(id);
  }

  Scope* GetScope(const ScopeId id) const{
//     std::cout << "asking: " << id<<std::endl;
    return scope_by_id_.at(id);
  }
  size_t NumScopes() const noexcept{ return free_scope_id_;};

  //TODO: are  these two used?
  bool ClassHasHScope(const std::string& class_name) const{
    auto it = hscope_by_class_name_.find(class_name);
    return it != hscope_by_class_name_.end();
  }
  HierarchicalScope& GetHScope(const std::string& class_name) const{
    const ScopeId id = hscope_by_class_name_.at(class_name);
    return dynamic_cast<HierarchicalScope&>(*scope_by_id_.at(id));
  }

  HierarchicalScope& GetHScope(const Type& class_type) const{
    const ScopeId id = hscope_by_class_typeid_.at(class_type.GetTypeId());
    return dynamic_cast<HierarchicalScope&>(*scope_by_id_.at(id));
  }


//   LexicalScope& Scope() noexcept{return *current_scope_;}
//   const LexicalScope& Scope() const noexcept{return *current_scope_;}

  LexicalScope& GetGlobalLexicalScope() noexcept {
    return *dynamic_cast<LexicalScope*>(GetScope(global_scope_id_));
  }

protected:
  const ScopeId FreeScopeId() noexcept{ return free_scope_id_++;}
  const ScopeOwnerId FreeScopeOwnerId() noexcept{ return free_scope_ownner_id_++;}
// private:
  ScopeId                 free_scope_id_;
  ScopeOwnerId            free_scope_ownner_id_;
  ScopeOwnerId            global_scope_ownner_id_;
  std::map<ScopeId,Scope*>   scope_by_id_;
  LexicalScope*     current_scope_;
  std::vector<PtrHierarchicalScope> hier_scopes_;
  std::map<std::string, ScopeId>    hscope_by_class_name_;
  std::map<TypeId, ScopeId>         hscope_by_class_typeid_;
  std::map<ScopeId,bool>            scope_is_lexical_or_hierarchical_;

  ScopeId global_scope_id_;

};


}//end namespace Compiler
