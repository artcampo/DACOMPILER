#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/VarIsMember.hpp"

namespace Compiler{

using namespace AST;


class VarIsMember : public Pass{
public:
  VarIsMember(CompilationUnit& unit)
    : Pass(unit
    , {CompUnitInfo::kAst, CompUnitInfo::kTypeCheck}
    , {CompUnitInfo::kVarIsMember}) {};

  virtual void Run(){
    if(unit_.ValidAst()){
      Visitor::VarIsMember v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("VarIsMember");
  };
};


}//end namespace Compiler
