#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "TypeTable.hpp"
#include "Node.hpp"
#include "Symbol.hpp"
#include "Function.hpp"
#include "IR/Offset.hpp"
#include <map>
#include <memory>

namespace Compiler{
namespace AST{

using AST::Ast;
using AST::LexicalScope;
using AST::Type;
using AST::Node;
using AST::ProgBody;
using AST::ScopeId;
using AST::SymbolTable;
using AST::DeclarationTable;
using namespace Compiler::AST::Ptrs;
using AST::FuncDecl;

class Function;
using PtrFunction = std::unique_ptr<Function>;

using OffsetTable = std::map<Symbols::SymbolId, IR::Offset>;

class Function{
public:

  Function(std::string& name, FuncDecl& origin_node): base_scope_(nullptr)
    , current_scope_(nullptr), name_(name), origin_node_(origin_node){}

  FuncDecl& GetFuncDeclNode() { return origin_node_; }
  const FuncDecl& GetFuncDeclNode() const { return origin_node_; }

  LexicalScope& Scope() noexcept{return *current_scope_;}
  const LexicalScope& Scope() const noexcept{return *current_scope_;}

  LexicalScope* NewFirstScope(const ScopeId free_scope_id){
    base_scope_ = new LexicalScope(free_scope_id, nullptr, symbol_table_
                        , declaration_table_, symbolid_of_node_);
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

  Symbols::Symbol& GetSymbolDecl(const Node& n){

  }

private:


  SymbolTable       symbol_table_;
  DeclarationTable  declaration_table_;
  LexicalScope*     base_scope_;
  LexicalScope*     current_scope_;
  FuncDecl&         origin_node_;
  OffsetTable       offset_table_;
  SymbolIdOfNode    symbolid_of_node_;

  std::string& name_;


};


}//end namespace AST
}//end namespace Compiler
