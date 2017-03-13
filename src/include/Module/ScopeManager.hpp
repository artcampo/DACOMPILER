#pragma once
#include "IR/Label.hpp"
#include <map>

namespace Compiler{

using AST::ScopeId;
using AST::Scope;
using AST::SymbolIdOfNode;
using AST::ScopeOwnerId;
using AST::PtrLexicalScope;
using AST::LexicalScope;

class ScopeManager{
public:
  ScopeManager() : free_scope_id_(0),  free_scope_ownner_id_(0)
  , global_scope_ownner_id_(0){
  }


  const ScopeOwnerId NewScopeOwner() noexcept{ return FreeScopeOwnerId(); }
  const ScopeOwnerId GlobalScopeOwnerId() const noexcept{ return global_scope_ownner_id_; }



  const ScopeId NewNestedScope(const ScopeOwnerId scope_owner_id){
    const ScopeId id = FreeScopeId();
    LexicalScope* new_scope;
    new_scope = current_scope_->NewNestedScope(id, scope_owner_id);
    scope_by_id_[id] = new_scope;
    current_scope_   = new_scope;
    return new_scope->GetScopeId();
  }

  void RestoreScope(){
//     std::cout << "*** restoring: " << current_scope_->str()<< "\n";
    current_scope_->UndoTables();
    current_scope_ = current_scope_->GetParentScope();
//     std::cout << "*** to: " << current_scope_->str()<< "\n";
  }

  LexicalScope* GetScope(const ScopeId id) const{
//     std::cout << "asking: " << id<<std::endl;
    return scope_by_id_.at(id);
  }
  size_t NumScopes() const noexcept{ return free_scope_id_;};
  LexicalScope& Scope() noexcept{return *current_scope_;}
  const LexicalScope& Scope() const noexcept{return *current_scope_;}



protected:
  const ScopeId FreeScopeId() noexcept{ return free_scope_id_++;}
  const ScopeOwnerId FreeScopeOwnerId() noexcept{ return free_scope_ownner_id_++;}
// private:
  ScopeId                 free_scope_id_;
  ScopeOwnerId            free_scope_ownner_id_;
  ScopeOwnerId            global_scope_ownner_id_;
  std::map<ScopeId,LexicalScope*>   scope_by_id_;
  LexicalScope*     current_scope_;


};


}//end namespace Compiler
