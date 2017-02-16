#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"
#include "Types.hpp"
#include <map>

namespace Compiler{

using AST::Ast;
using AST::LexicalScope;
using AST::TypeId;
using AST::Node;
using AST::ScopeId;

class CompilationUnit {
public:

  CompilationUnit(): ast_(), main_scope_(nullptr), current_scope_(nullptr),
    free_scope_id_(0){}

  const bool ValidAst() const noexcept { return ast_.block_ != nullptr; }
  LexicalScope& Scope() noexcept{return *current_scope_;}
  const LexicalScope& Scope() const noexcept{return *current_scope_;}

  ScopeId NewFirstScope(){
    main_scope_ = new LexicalScope(free_scope_id_, nullptr);
    ++free_scope_id_;
    current_scope_ = main_scope_;
  }

  const ScopeId NewNestedScope(){
    LexicalScope* new_scope = current_scope_->NewNestedScope(free_scope_id_);
    ++free_scope_id_;
    current_scope_ = new_scope;
    return new_scope->GetScopeId();
  }

  void RestoreScope(){
    current_scope_ = current_scope_->GetParentScope();
  }

  Ast            ast_;

  void RecordType(const Node* n, const TypeId& t){
    type_info_[n]=t;
  }
  TypeId GetTypeId(const Node* n){
    return type_info_[n];
  }

  void Error(const std::string& e){
    std::cout << e << "\n";
  }
private:
  std::map<const Node*,TypeId> type_info_;

  LexicalScope*  main_scope_;
  LexicalScope*  current_scope_;
  ScopeId        free_scope_id_;

};


}//end namespace Compiler
