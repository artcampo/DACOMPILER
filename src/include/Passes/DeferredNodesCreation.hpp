#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/DeferredNodesCreation.hpp"
#include "ASTVisitors/ASTVisitorTypeInference.hpp"

namespace Compiler{

using namespace AST;


class DeferredNodesCreation : public Pass{
public:
  DeferredNodesCreation(CompilationUnit& unit
  , ASTVisitorTypeInference& type_inf_visitor)
    : Pass(unit
      , {CompUnitInfo::kAstIncomplete1}
      , {CompUnitInfo::kAstIncomplete2})
    , type_inf_visitor_(type_inf_visitor){};

  virtual void Run(){
    if(unit_.ValidAst()){
      Visitor::DeferredNodesCreation v(unit_, type_inf_visitor_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("DeferredNodesCreation");
  };

private:
  ASTVisitorTypeInference& type_inf_visitor_;
};


}//end namespace Compiler
