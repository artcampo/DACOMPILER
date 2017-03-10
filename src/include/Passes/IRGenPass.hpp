#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "ErrorLog/Messages.hpp"
#include "CompilationUnit.hpp"
#include "IR/IRGenerator.hpp"

class IRGenerator : public Pass{
public:
  IRGenerator(CompilationUnit& unit)
    : Pass(unit
        , { CompUnitInfo::kAst
          , CompUnitInfo::kLnessRnessOfNode
          , CompUnitInfo::kTypeOfNode
          , CompUnitInfo::kVarAccessIsValOrAddress}
        , { CompUnitInfo::kIR}){};

  virtual void Run(){
    if(unit_.ValidAst()){
      ASTVisitorIRGenerator v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("IR generator");
  };

};
