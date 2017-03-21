#pragma once
#include "AST/AST.hpp"
#include "Function.hpp"
#include "Scopes/LexicalScope.hpp"
#include "IR/Label.hpp"
#include <map>
#include <cassert>

namespace Compiler{

using AST::FuncDef;
using AST::FuncDecl;
using AST::PtrFunction;
using AST::Function;
using AST::OffsetTable;
using AST::ScopeOwnerId;
using IR::Label;

class FunctionManager{
public:
  FunctionManager() :
      curr_func_(nullptr)
    , curr_func_decl_(nullptr){}

  AST::Function* CurrentFunction() const noexcept { return curr_func_;}

  bool      InsideFunctionDefinition() const noexcept { return curr_func_decl_ != nullptr; }
  FuncDecl& CurrentFuncDecl() const noexcept { return *curr_func_decl_; }

  Function& GetFunc(const std::string& name){ return *function_by_name_.at(name);}
  const Function& GetFunc(const std::string& name) const { return *function_by_name_.at(name);}

  Function& GetFunc(const FuncDef& n){
    return *function_by_funcdef_.at(const_cast<FuncDef*>(&n));
  }
  const Function& GetFunc(const FuncDef& n) const{
    return *function_by_funcdef_.at(const_cast<FuncDef*>(&n));
  }

  //Create regular function
  void NewFunction(const std::string& name
    , OffsetTable& module_offset_table
    , const ScopeOwnerId scope_owner_id
    , const Label entry, const Label local){
    functions_.push_back( std::move(
      Function::NewFunction(name
        , module_offset_table
        , scope_owner_id
        , entry
        , local)));
    curr_func_ = functions_.back().get();
    function_by_name_[name] = curr_func_;
  }

  //Create member function
  Function& NewFunction(const std::string& name
    , const std::string& class_name
    , OffsetTable& module_offset_table
    , const ScopeOwnerId scope_owner_id
    , const Label entry, const Label local){
    functions_.push_back( std::move(
      Function::NewMemberFunction(name
        , class_name
        , module_offset_table
        , scope_owner_id
        , entry
        , local)));
    curr_func_ = functions_.back().get();
    function_by_name_[name] = curr_func_;
    return *functions_.back();
  }



  void EnterFunctionDefinition(FuncDecl* current_func_decl){
    curr_func_decl_ = current_func_decl;
  }
  void ExitFunctionDefinition(){
    curr_func_ = nullptr;
    curr_func_decl_ = nullptr;
  }

  void SetFuncOriginNode(const FuncDef& n){
    assert(curr_func_ != nullptr); // "SetFunc in no func");
    function_by_funcdef_[const_cast<FuncDef*>(&n)] = curr_func_;
    curr_func_->SetOriginNode(n);
  }

protected:
  std::vector<AST::PtrFunction> functions_;
private:


  AST::Function*  curr_func_;
  FuncDecl*       curr_func_decl_;

  std::map<FuncDef*, Function*>     function_by_funcdef_;
  std::map<std::string, Function*>  function_by_name_;

};


}//end namespace Compiler
