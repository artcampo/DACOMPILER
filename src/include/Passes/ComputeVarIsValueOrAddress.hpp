#pragma once
#include "Passes/Pass.hpp"
#include "ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/VarIsValueOrAddress.hpp"

namespace Compiler{

using namespace AST;


class ComputeVarIsValueOrAddress : public Pass{
public:
  ComputeVarIsValueOrAddress(CompilationUnit& unit)
    : Pass(unit
      , {CompUnitInfo::kAst}
      , {CompUnitInfo::kVarAccessIsValOrAddress}) {};

  virtual void Run(){
    if(unit_.ValidAst()){
      VarIsValueOrAddress v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("Compute VarIsValueOrAddress");
  };
};


}//end namespace Compiler
