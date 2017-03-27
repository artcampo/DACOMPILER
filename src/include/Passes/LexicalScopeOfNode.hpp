#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/LexicalScopeOfNode.hpp"

namespace Compiler{

using namespace AST;

class LexicalScopeOfNode : public Pass{
public:
  LexicalScopeOfNode(CompilationUnit& unit)
    : Pass(unit
        , {CompUnitInfo::kAst}
        , {CompUnitInfo::kLexicalScopeOfNode})
    , v_(unit_){};

  virtual void Run(){
    if(unit_.ValidAst()){
      v_.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("LexicalScopeOfNode");
  };

  Visitor::LexicalScopeOfNode v_;

};


}//end namespace Compiler
