#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "TypeTable.hpp"
#include <map>
#include <memory>

namespace Compiler{

using AST::Ast;
using AST::LexicalScope;
using AST::Type;
using AST::Node;
using AST::ProgBody;
using AST::ScopeId;
using AST::SymbolTable;
using AST::DeclarationTable;
using namespace Compiler::AST::Ptrs;

class Function;
using PtrFunction = std::unique_ptr<Function>;

class Function{
public:

  Function(std::string& name): base_scope_(nullptr), current_scope_(nullptr)
    , name_(name){}


  LexicalScope& Scope() noexcept{return *current_scope_;}
  const LexicalScope& Scope() const noexcept{return *current_scope_;}

  LexicalScope* NewFirstScope(const ScopeId free_scope_id){
    base_scope_ = new LexicalScope(free_scope_id, nullptr, symbol_table_, declaration_table_);
    current_scope_ = base_scope_;
    return base_scope_;
  }


  LexicalScope* NewNestedScope(const ScopeId free_scope_id){
    //TODO: store in unique!!
    LexicalScope* new_scope = current_scope_->NewNestedScope(free_scope_id);
    current_scope_ = new_scope;
    return new_scope;
  }

  void RestoreScope(){
    current_scope_->UndoTables();
    current_scope_ = current_scope_->GetParentScope();
  }

private:

  SymbolTable       symbol_table_;
  DeclarationTable  declaration_table_;
  LexicalScope*     base_scope_;
  LexicalScope*     current_scope_;


  std::string& name_;


};


}//end namespace Compiler
