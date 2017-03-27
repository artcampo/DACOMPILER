#pragma once
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "ErrorLog.hpp"
#include "TreeDecoration.hpp"
#include "AST/AST.hpp"
#include "Scopes/Scope.hpp"
#include "Scopes/LexicalScope.hpp"
#include "IR/Label.hpp"
#include "Module/TypeTable.hpp"
#include "Module/LabelManager.hpp"
#include "Module/FunctionManager.hpp"
#include "Module/ClassManager.hpp"
#include "Module/ScopeManager.hpp"
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
// class Compiler::AST::Dump;
// class ASTVisitor;
// namespace AST{ class Dump; class Function;};
namespace AST{ class Dump;};

using AST::PtrLexicalScope;
using AST::Scope;
using AST::SymbolIdOfNode;
// using AST::OffsetTable;
using AST::ScopeOwnerId;
using IR::Label;

class CompilationUnit : public TreeDecoration, public TypeTable
  , public LabelManager, public ScopeManager, public FunctionManager
  , public ClassManager
  {
public:

  CompilationUnit(): 
      TypeTable(error_log_)
    , ScopeManager()
    , FunctionManager()
    , ClassManager(this, this, this, this)
    , ast_()
    , free_symbol_id_(AST::Symbols::Symbol::InitialFreeId())
    , module_scope_(std::move(GlobalLexicalScope(symbol_table_
        , module_declaration_table_, symbolid_of_node_)))
    , module_declaration_table_()

    {
      scope_by_id_[GlobalScopeId( GlobalScopeOwnerId() )] = module_scope_.get();
      current_scope_ = module_scope_.get();
    }


  const ScopeId NewFunction(const std::string& name, const ScopeOwnerId scope_owner_id){
    const Label entry = NewFunctionEntryLabel(name);
    Label local;
    if(name == "main")  local = GetLabelMainLocals();
    else                local = NewFunctionARLabel(name);
    FunctionManager::NewFunction(name, ModuleOffsetTable(), scope_owner_id
      , entry, local);
    return NewNestedScope(scope_owner_id);
  }


  const ScopeId NewFunction(const std::string& name, const std::string& class_name
    , const ScopeOwnerId scope_owner_id){
    const std::string mangled_name = Function::MangledName(name, class_name);
    const Label entry = NewFunctionEntryLabel(mangled_name);
    Label local       = NewFunctionARLabel(mangled_name);
    Function& f = FunctionManager::NewFunction(name, class_name
      , ModuleOffsetTable(), scope_owner_id, entry, local);
    return NewNestedScope(scope_owner_id);
  }

  const Type& GetType(const std::string& name, const ScopeId scope_id){
//     if(ScopeIsLexical(scope_id))
    return GetScope(scope_id)->GetType(name);
  }
  const Type& GetType(const TypeId id) const{ return TypeTable::GetType(id);}

  bool RegisterDecl(const std::string& name, const Type& type, const Node& n
    , const ScopeId scope_id){
    AST::Symbols::SymbolId symbol_id = free_symbol_id_;
    bool registered = GetScope(scope_id)->RegisterDecl(name, type, n, free_symbol_id_);
//     std::cout << "Register: " << name << " in " << GetScope(scope_id)->str()<<"\n";
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

  ScopeId GlobalScopeId(const ScopeOwnerId scope_owner_id){
//     std::cout << scope_owner_id<<" "<<module_scope_->GetScopeOwnerId();
//     assert(scope_owner_id == module_scope_->GetScopeOwnerId());
    return module_scope_->GetScopeId();
  }

private:
  AST::Symbols::SymbolId  free_symbol_id_;
  SymbolTable       symbol_table_;
  DeclarationTable  module_declaration_table_;
  ErrorLog          error_log_;
  Ast               ast_;
  PtrLexicalScope   module_scope_;


  //Referencing structures
  SymbolIdOfNode                    symbolid_of_node_;


public:
  friend class AST::Dump;

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
    error_log_.Error(message);
  }

  bool HasErrors() const noexcept {return error_log_.NumErrors() > 0;}
};

// namespace CompilationUnitInfo{
  enum class CompUnitInfo : size_t{
      kAst = 0
    , kTypeOfNode = 1
    , kLnessRnessOfNode = 2
    , kLocalVarOffsets = 3
    , kVarAccessIsReadOrWrite = 4
    , kVarAccessIsValOrAddress = 5
    , kIR = 6
    , kAstIncomplete1 = 7
    , kAstIncomplete2 = 8
    , kTypeCheck = 9
    , kVarIsMember = 10
    , kLexicalScopeOfNode = 11
  };
// }

}//end namespace Compiler
