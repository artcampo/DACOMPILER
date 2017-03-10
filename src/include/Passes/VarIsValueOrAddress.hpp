#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/VarIsValueOrAddress.hpp"

namespace Compiler{

using namespace AST;


class VarIsValueOrAddress : public Pass{
public:
  VarIsValueOrAddress(CompilationUnit& unit)
    : Pass(unit
      , {CompUnitInfo::kAst}
      , {CompUnitInfo::kVarAccessIsValOrAddress}) {};

  virtual void Run(){
    if(unit_.ValidAst()){
      Visitor::VarIsValueOrAddress v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("VarIsValueOrAddress");
  };
};


}//end namespace Compiler
