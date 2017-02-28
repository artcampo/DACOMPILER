#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "TypeTable.hpp"
#include "ErrorLog.hpp"
#include "LnessRness.hpp"
#include "LabelManager.hpp"
#include "Function.hpp"
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
// class Compiler::AST::ASTVisitorDump;
// class ASTVisitor;
namespace AST{ class ASTVisitorDump;};

class CompilationUnit : public LnessRness, public TypeTable
  , public LabelManager{
public:

  CompilationUnit(): ast_(), free_scope_id_(0), TypeTable(error_log_)
    , curr_func_(nullptr){}


  LexicalScope& Scope() noexcept{return curr_func_->Scope();}
  const LexicalScope& Scope() const noexcept{return curr_func_->Scope();}

  void NewFunction(std::string& name){
    functions_.push_back( std::move( std::make_unique<Function>(name)));
    curr_func_ = functions_[ functions_.size() - 1].get();
  }

  ScopeId NewFirstScope(){
    const ScopeId id = FreeScopeId();
    scope_by_id_[id] = curr_func_->NewFirstScope(id);
    return id;
  }

  const ScopeId NewNestedScope(){
    const ScopeId id = FreeScopeId();
    LexicalScope* new_scope = curr_func_->NewNestedScope(id);
    scope_by_id_[id] = new_scope;
    return new_scope->GetScopeId();
  }

  void RestoreScope(){ curr_func_->RestoreScope();}

  const bool ValidAst() const noexcept { return ast_.prog_ != nullptr; }

  void InitAst(PtrProgBody& prog){
    ast_.prog_ = std::move(prog);
  }

//   const Prog* GetAstProg() const noexcept{ return *ast_.prog_;}
  ProgBody* GetAstProg() noexcept{ return ast_.prog_.get();}

  void SetTypeOfNode(const Node& n, const Type& t){
//     std::cout << "Set: " << n->str() << ": " << t.str() << "\n";
    type_of_node_[&n]=&t;
  }

  const Type& GetTypeOfNode(const Node& n){
//     std::cout << "Get: " << n->str() << ": " << type_of_node_[n]->str() << "\n";
    return *type_of_node_[&n];
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
  std::map<const Node*, const Type* > type_of_node_;
  std::map<ScopeId,LexicalScope*> scope_by_id_;


  ScopeId           free_scope_id_;
  ErrorLog          error_log_;
  Ast               ast_;

  std::vector<PtrFunction> functions_;
  Function*         curr_func_;

  const ScopeId FreeScopeId() noexcept{ ++free_scope_id_; return free_scope_id_ - 1;}


public:
  friend class AST::ASTVisitorDump;
//   friend class ASTVisitor;
};

// namespace CompilationUnitInfo{
  enum class CompUnitInfo : size_t{
      kAst = 0
    , kTypeOfNode = 1
    , kLnessRnessOfNode = 2
    , kIR = 3
  };
// }

}//end namespace Compiler
