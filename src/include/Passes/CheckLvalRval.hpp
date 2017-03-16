#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/LvalRval.hpp"

namespace Compiler{

using namespace AST;


class CheckLvalRval : public Pass{
public:
  CheckLvalRval(CompilationUnit& unit)
    : Pass(unit
      , {CompUnitInfo::kAst}
      , { CompUnitInfo::kLnessRnessOfNode
        , CompUnitInfo::kVarAccessIsReadOrWrite}) {};

  virtual void Run(){
    if(unit_.ValidAst()){
      LvalRval v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("Check Lval/Rval");
  };
};


}//end namespace Compiler
