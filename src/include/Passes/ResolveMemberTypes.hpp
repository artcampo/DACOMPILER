#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/ResolveMemberTypes.hpp"

namespace Compiler{

using namespace AST;


class ResolveMemberTypes : public Pass{
public:
  ResolveMemberTypes(CompilationUnit& unit)
    : Pass(unit
      , {CompUnitInfo::kAstIncomplete1}
      , {CompUnitInfo::kAstIncomplete2}){}

  virtual void Run(){
    if(unit_.ValidAst()){
      Visitor::ResolveMemberTypes v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("ResolveMemberTypes");
  };
};


}//end namespace Compiler
