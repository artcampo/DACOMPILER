#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/TypeInference.hpp"

namespace Compiler{

using namespace AST;

class TypeInference : public Pass{
public:
  TypeInference(CompilationUnit& unit)
    : Pass(unit
        , {CompUnitInfo::kAst, CompUnitInfo::kLnessRnessOfNode}
        , {CompUnitInfo::kTypeOfNode})
    , v_(unit_){};

  virtual void Run(){
    if(unit_.ValidAst()){
      v_.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("Type inference");
  };

  Visitor::TypeInference v_;

};


}//end namespace Compiler
