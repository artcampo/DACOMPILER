#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "TypeTable.hpp"
#include "ErrorLog.hpp"
#include "TreeDecoration.hpp"
#include "LabelManager.hpp"
#include "Function.hpp"
#include "IR/Label.hpp"
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
using AST::FuncDef;
using AST::FuncDecl;
using AST::PtrFunction;
using AST::Function;
using AST::PtrLexicalScope;
using AST::SymbolIdOfNode;
using AST::OffsetTable;
using AST::ScopeOwnerId;
using IR::Label;

class CompilationUnit : public TreeDecoration, public TypeTable
  , public LabelManager{
public:

  CompilationUnit(): ast_(), free_scope_id_(0), free_symbol_id_(0)
    , free_scope_ownner_id_(0), TypeTable(error_log_)
    , curr_func_(nullptr)
    , curr_func_decl_(nullptr)
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

  const ScopeId NewFunction(std::string& name, const ScopeOwnerId scope_owner_id){
    const Label entry = NewFunctionEntryLabel(name);
    Label local;
    if(name == "main")  local = GetLabelMainLocals();
    else                local = NewFunctionARLabel(name);

    functions_.push_back( std::move(
      std::make_unique<Function>(name
        , ModuleOffsetTable()
        , scope_owner_id
        , entry
        , local)));
    curr_func_ = functions_[ functions_.size() - 1].get();
    function_by_name_[name] = curr_func_;
    return NewNestedScope(scope_owner_id);
  }

  void EnterFunctionDefinition(FuncDecl* current_func_decl){
    curr_func_decl_ = current_func_decl;
  }
  void ExitFunctionDefinition(){
    curr_func_ = nullptr;
    curr_func_decl_ = nullptr;
    RestoreScope();
  }

  void SetFuncOriginNode(const FuncDef& n){
    assert(curr_func_ != nullptr); // "SetFunc in no func");
    function_by_funcdef_[const_cast<FuncDef*>(&n)] = curr_func_;
    curr_func_->SetOriginNode(n);
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


  Function& GetFunc(const std::string& name){ return *function_by_name_.at(name);}
  const Function& GetFunc(const std::string& name) const { return *function_by_name_.at(name);}

  Function& GetFunc(const FuncDef& n){
    return *function_by_funcdef_.at(const_cast<FuncDef*>(&n));
  }
  const Function& GetFunc(const FuncDef& n) const{
    return *function_by_funcdef_.at(const_cast<FuncDef*>(&n));
  }

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
      if(curr_func_ != nullptr){
        curr_func_->StoreDecl( *module_declaration_table_[symbol_id], n);
//         std::cout << "Reg: n:"<< &n << " s: " <<module_declaration_table_[symbol_id].get()
//         << " symbol: " << module_declaration_table_[symbol_id]->str()
//         << " " << n.str()
//         << std::endl;
      }
    }
    return registered;
  }

  bool      InsideFunctionDefinition() const noexcept { return curr_func_decl_ != nullptr; }
  FuncDecl& CurrentFuncDecl() const noexcept { return *curr_func_decl_; }

private:
  ScopeId                 free_scope_id_;
  AST::Symbols::SymbolId  free_symbol_id_;
  ScopeOwnerId            free_scope_ownner_id_;
  ScopeOwnerId            global_scope_ownner_id_;

  SymbolTable       symbol_table_;
  DeclarationTable  module_declaration_table_;

  ErrorLog          error_log_;
  Ast               ast_;

  std::vector<AST::PtrFunction> functions_;
  AST::Function*          curr_func_;
  FuncDecl*                curr_func_decl_;

  PtrLexicalScope   module_scope_;
  LexicalScope*     current_scope_;


  //Referencing structures
  std::map<ScopeId,LexicalScope*>   scope_by_id_;
  std::map<std::string, Function*>  function_by_name_;
  SymbolIdOfNode                    symbolid_of_node_;
  std::map<FuncDef*, Function*>     function_by_funcdef_;

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
