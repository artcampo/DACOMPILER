#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "ErrorLog.hpp"
#include "LnessRness.hpp"
#include <map>
#include <memory>

namespace Compiler{

using AST::Ast;
using AST::LexicalScope;
using AST::TypeId;
using AST::Node;
using AST::ProgBody;
using AST::ScopeId;
using AST::SymbolTable;
using AST::DeclarationTable;

class CompilationUnit : public LnessRness{
public:

  CompilationUnit(): ast_(), main_scope_(nullptr), current_scope_(nullptr),
    free_scope_id_(0){}

  LexicalScope& Scope() noexcept{return *current_scope_;}
  const LexicalScope& Scope() const noexcept{return *current_scope_;}

  ScopeId NewFirstScope(){
    const ScopeId id = free_scope_id_;
    main_scope_ = new LexicalScope(id, nullptr, symbol_table_, declaration_table_);
    scope_by_id_[id] = main_scope_;
    ++free_scope_id_;
    current_scope_ = main_scope_;
    return id;
  }

  const ScopeId NewNestedScope(){
    LexicalScope* new_scope = current_scope_->NewNestedScope(free_scope_id_);
    scope_by_id_[free_scope_id_] = new_scope;
    ++free_scope_id_;
    current_scope_ = new_scope;
    return new_scope->GetScopeId();
  }

  void RestoreScope(){
    current_scope_->UndoTables();
    current_scope_ = current_scope_->GetParentScope();
  }

  const bool ValidAst() const noexcept { return ast_.prog_ != nullptr; }

  void InitAst(std::unique_ptr<ProgBody>& prog){
    ast_.prog_ = std::move(prog);
  }

//   const Prog* GetAstProg() const noexcept{ return *ast_.prog_;}
  ProgBody* GetAstProg() noexcept{ return ast_.prog_.get();}


  void RecordType(const Node* n, const TypeId& t){
    type_info_[n]=t;
  }
  TypeId GetTypeId(const Node* n){
    return type_info_[n];
  }

  LexicalScope* GetScope(const ScopeId id) const{
//     std::cout << "asking: " << id<<std::endl;
    return scope_by_id_.at(id);
  }
  size_t NumScopes() const noexcept{ return free_scope_id_;};

  void SetFileData(std::vector<char>* file_data){
    error_log_.SetFileData(file_data);
  }

  void Error(const std::string& message, const Locus& locus){
    error_log_.Error(message, locus);
  }

  void Error(const std::string& message){
    std::cout << message << "\n";
  }



private:
  std::map<const Node*,TypeId> type_info_;
  std::map<ScopeId,LexicalScope*> scope_by_id_;
  SymbolTable       symbol_table_;
  DeclarationTable  declaration_table_;
  LexicalScope*     main_scope_;
  LexicalScope*     current_scope_;
  ScopeId           free_scope_id_;
  ErrorLog          error_log_;
  Ast               ast_;

public:


};

// namespace CompilationUnitInfo{
  enum class CompUnitInfo : size_t{
      kAst = 0
    , kTypeOfNode = 1
    , kLnessRnessOfNode = 2
  };
// }

}//end namespace Compiler
