#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/TypeCheck.hpp"

namespace Compiler{

using namespace AST;

class TypeCheck : public Pass{
public:
  TypeCheck(CompilationUnit& unit)
    : Pass(unit
        , {CompUnitInfo::kAst, CompUnitInfo::kLnessRnessOfNode
          , CompUnitInfo::kTypeOfNode}
        , {CompUnitInfo::kTypeCheck})
    , v_(unit_){};

  virtual void Run(){
    if(unit_.ValidAst()){
      v_.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("TypeCheck");
  };

  Visitor::TypeCheck v_;

};


}//end namespace Compiler
