#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/VarIsReadOrWrite.hpp"

namespace Compiler{

using namespace AST;


class VarIsReadOrWrite : public Pass{
public:
  VarIsReadOrWrite(CompilationUnit& unit)
    : Pass(unit
      , {CompUnitInfo::kAst}
      , {CompUnitInfo::kVarAccessIsReadOrWrite}) {};

  virtual void Run(){
    if(unit_.ValidAst()){
      Visitor::VarIsReadOrWrite v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("VarIsReadOrWrite");
  };
};


}//end namespace Compiler
