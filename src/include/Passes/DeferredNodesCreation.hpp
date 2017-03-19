#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/DeferredNodesCreation.hpp"
#include "ASTVisitors/TypeInference.hpp"

namespace Compiler{

using namespace AST;


class DeferredNodesCreation : public Pass{
public:
  DeferredNodesCreation(CompilationUnit& unit
  , Visitor::TypeInference& type_inf_visitor)
    : Pass(unit
    , {CompUnitInfo::kAstIncomplete2}
    , {CompUnitInfo::kAst})
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
  Visitor::TypeInference& type_inf_visitor_;
};


}//end namespace Compiler
