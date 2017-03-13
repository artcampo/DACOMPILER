#pragma once
#include "AST/AST.hpp"
#include "Scopes/LexicalScope.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "ErrorLog.hpp"
#include "TreeDecoration.hpp"
#include "IR/Label.hpp"
#include "Module/TypeTable.hpp"
#include "Module/LabelManager.hpp"
#include "Module/FunctionManager.hpp"
#include "Module/ClassManager.hpp"
#include <map>
#include <memory>
#include <iterator>
#include <stack>
#include <cassert>

namespace Compiler{

using AST::Ast;
using AST::LexicalScope;
using AST::Type;
using AST::Node;
using AST::Var;
using AST::Expr;
using AST::ProgBody;
using AST::ScopeId;
using AST::SymbolTable;
using AST::DeclarationTable;
using namespace Compiler::AST::Ptrs;
// class Compiler::AST::ASTVisitorDump;
// class ASTVisitor;
// namespace AST{ class ASTVisitorDump; class Function;};
namespace AST{ class ASTVisitorDump;};

using AST::PtrLexicalScope;
using AST::SymbolIdOfNode;
// using AST::OffsetTable;
using AST::ScopeOwnerId;
using IR::Label;

class CompilationUnit : public TreeDecoration, public TypeTable
  , public LabelManager, public ClassManager, public FunctionManager{
public:

  CompilationUnit(): ast_(), free_scope_id_(0), free_symbol_id_(0)
    , free_scope_ownner_id_(0), TypeTable(error_log_)
    , module_scope_(std::move(std::make_unique<LexicalScope>
        (FreeScopeId(), nullptr, FreeScopeOwnerId(), symbol_table_
        , module_declaration_table_, symbolid_of_node_)))
    , current_scope_(module_scope_.get())
    , module_declaration_table_()
    , global_scope_ownner_id_(0)
    {
      scope_by_id_[GlobalScopeId( GlobalScopeOwnerId() )] = module_scope_.get();
    }

  LexicalScope& Scope() noexcept{return *current_scope_;}
  const LexicalScope& Scope() const noexcept{return *current_scope_;}


  void NewClass(std::string& name){
    ClassManager::NewClass(name, NewScopeOwner(), FreeScopeId());
  }

  const ScopeId NewFunction(std::string& name, const ScopeOwnerId scope_owner_id){
    const Label entry = NewFunctionEntryLabel(name);
    Label local;
    if(name == "main")  local = GetLabelMainLocals();
    else                local = NewFunctionARLabel(name);

    FunctionManager::NewFunction(name, ModuleOffsetTable(), scope_owner_id
      , entry, local);

    return NewNestedScope(scope_owner_id);
  }

  const ScopeOwnerId NewScopeOwner() noexcept{ return FreeScopeOwnerId(); }
  const ScopeOwnerId GlobalScopeOwnerId() const noexcept{ return global_scope_ownner_id_; }

  ScopeId GlobalScopeId(const ScopeOwnerId scope_owner_id){
//     std::cout << scope_owner_id<<" "<<module_scope_->GetScopeOwnerId();
    assert(scope_owner_id == module_scope_->GetScopeOwnerId());
    return module_scope_->GetScopeId();
  }

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




  bool IsDeclValid(const std::string& name){return Scope().IsDeclValid(name);}
  bool HasDecl(const std::string& name){return Scope().HasDecl(name);}
  const Type& GetType(const std::string& name){
    return module_declaration_table_.at(Scope().DeclId(name))->GetType();
  }
  const Type& GetType(const TypeId id) const{ return TypeTable::GetType(id);}


  bool RegisterDecl(const std::string& name, const Type& type, const Node& n){
    AST::Symbols::SymbolId symbol_id = free_symbol_id_;
    bool registered = Scope().RegisterDecl(name, type, n, free_symbol_id_);
    if(registered){
      symbolid_of_node_[&n] = symbol_id;
      ++free_symbol_id_;
      if(CurrentFunction() != nullptr){
        CurrentFunction()->StoreDecl( *module_declaration_table_[symbol_id], n);
//         std::cout << "Reg: n:"<< &n << " s: " <<module_declaration_table_[symbol_id].get()
//         << " symbol: " << module_declaration_table_[symbol_id]->str()
//         << " " << n.str()
//         << std::endl;
      }
    }
    return registered;
  }



private:
  ScopeId                 free_scope_id_;
  AST::Symbols::SymbolId  free_symbol_id_;
  ScopeOwnerId            free_scope_ownner_id_;
  ScopeOwnerId            global_scope_ownner_id_;

  SymbolTable       symbol_table_;
  DeclarationTable  module_declaration_table_;

  ErrorLog          error_log_;
  Ast               ast_;



  PtrLexicalScope   module_scope_;
  LexicalScope*     current_scope_;

  //Referencing structures
  std::map<ScopeId,LexicalScope*>   scope_by_id_;
  SymbolIdOfNode                    symbolid_of_node_;


  //Attributes computed by visitors

  const ScopeId FreeScopeId() noexcept{ return free_scope_id_++;}
  const ScopeOwnerId FreeScopeOwnerId() noexcept{ return free_scope_ownner_id_++;}


public:
  friend class AST::ASTVisitorDump;

  using iterator = std::vector<PtrFunction>::iterator;
  using const_iterator = std::vector<PtrFunction>::const_iterator;

  iterator begin() { return functions_.begin(); }
  iterator end()   { return functions_.end(); }
  const_iterator begin()  const { return functions_.begin(); }
  const_iterator end()    const { return functions_.end(); }
  const_iterator cbegin() const { return functions_.cbegin(); }
  const_iterator cend()   const { return functions_.cend(); }

  const bool ValidAst() const noexcept { return ast_.prog_ != nullptr; }

  void InitAst(PtrProgBody& prog){
    ast_.prog_ = std::move(prog);
  }

//   const Prog* GetAstProg() const noexcept{ return *ast_.prog_;}
  ProgBody* GetAstProg() noexcept{ return ast_.prog_.get();}

  void SetFileData(std::vector<char>* file_data){
    error_log_.SetFileData(file_data);
  }

  void Error(const std::string& message, const Locus& locus){
    error_log_.Error(message, locus);
  }

  void Error(const std::string& message){
    std::cout << message << "\n";
  }
};

// namespace CompilationUnitInfo{
  enum class CompUnitInfo : size_t{
      kAst = 0
    , kTypeOfNode = 1
    , kLnessRnessOfNode = 2
    , kLocalVarOffsets = 3
    , kVarAccessIsReadOrWrite = 4
    , kVarAccessIsValOrAddress = 5
    , kIR
  };
// }

}//end namespace Compiler
