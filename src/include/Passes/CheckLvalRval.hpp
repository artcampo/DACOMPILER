#pragma once
#include "Passes/Pass.hpp"
#include "ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"

namespace Compiler{

using namespace AST;

class ASTVisitorLvalRval : public ASTVisitor{
public:

  ASTVisitorLvalRval(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(ProgBody const& p){
    p.GetProgInit()->Accept(*this);
    p.GetBlock()->Accept(*this);
    p.GetProgEnd()->Accept(*this);
  }

  virtual void Visit(Block const& p){
    for (auto c : p.statements) c->Accept(*this);
  }

  virtual void Visit(IfStmt const& p){
    p.GetCond()->Accept(*this);
    p.GetThen()->Accept(*this);
    if(p.HasElse()) p.GetElse()->Accept(*this);
  }

  virtual void Visit(WhileStmt const& p){
    p.GetCond()->Accept(*this);
    p.GetBody()->Accept(*this);
  }

  virtual void Visit(BinaryOp const& p){
    p.Lhs()->Accept(*this);
    p.Rhs()->Accept(*this);
    unit_.SetNodeAsRval(p);
  }

  virtual void Visit(AssignStmt const& p){
    p.Lhs()->Accept(*this);
    p.Rhs()->Accept(*this);

    if(not unit_.IsLValue(*p.Lhs()))
      unit_.Error(kErr22, p.Lhs()->GetLocus());
  }

  virtual void Visit(RefOp const& p){
    p.Rhs()->Accept(*this);
    if(not unit_.IsLValue(*p.Rhs()))
      unit_.Error(kErr23, p.Rhs()->GetLocus());
  }

  virtual void Visit(DerefOp const& p){
    p.Rhs()->Accept(*this);
    if(not unit_.IsLValue(*p.Rhs()))
      unit_.Error(kErr24, p.Rhs()->GetLocus());
  }

  virtual void Visit(Literal const& p){unit_.SetNodeAsRval(p);}
  virtual void Visit(Var const& p)    {unit_.SetNodeAsLval(p);}

  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}
//   virtual void Visit(UnaryOp const& p){}


private:
  CompilationUnit&  unit_;
};

class CheckLvalRval : public Pass{
public:
  CheckLvalRval(CompilationUnit& unit)
    : Pass(unit, {CompUnitInfo::kAst}, {CompUnitInfo::kLnessRnessOfNode}) {};

  virtual void Run(){
    if(unit_.ValidAst()){
      ASTVisitorLvalRval v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("Check Lval/Rval");
  };
};


}//end namespace Compiler
