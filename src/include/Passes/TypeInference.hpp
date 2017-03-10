#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/ASTVisitorTypeInference.hpp"

namespace Compiler{

using namespace AST;

class TypeInference : public Pass{
public:
  TypeInference(CompilationUnit& unit)
    : Pass(unit
        , {CompUnitInfo::kAst, CompUnitInfo::kLnessRnessOfNode}
        , {CompUnitInfo::kTypeOfNode}){};

  virtual void Run(){
    if(unit_.ValidAst()){
      ASTVisitorTypeInference v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("Type inference");
  };

};


}//end namespace Compiler
