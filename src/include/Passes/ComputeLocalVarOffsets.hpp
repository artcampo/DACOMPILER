#pragma once
#include "Passes/Pass.hpp"
#include "ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/LocalVarOffsets.hpp"

namespace Compiler{

using namespace AST;


class ComputeLocalVarOffsets : public Pass{
public:
  ComputeLocalVarOffsets(CompilationUnit& unit)
    : Pass(unit, {CompUnitInfo::kAst}, {CompUnitInfo::kLocalVarOffsets}) {};

  virtual void Run(){
    if(unit_.ValidAst())
      for(auto& f : unit_){
        LocalVarOffsets v(unit_, *f);
        v.Visit(f->GetFuncDefNode());
      }
  };

  virtual std::string str() const noexcept{
    return std::string("Compute Local Var Offsets");
  };
};


}//end namespace Compiler
