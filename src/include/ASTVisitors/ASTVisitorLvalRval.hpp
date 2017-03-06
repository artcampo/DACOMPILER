#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{

class ASTVisitorLvalRval : public ASTVisitor{
public:

  ASTVisitorLvalRval(CompilationUnit& unit)
    : unit_(unit){};

  virtual void Visit(ProgBody const& p){
    p.GetProgInit().Accept(*this);
    for(auto& it : p) it->Accept(*this);
    p.GetProgEnd().Accept(*this);
  }

  virtual void Visit(FuncDef const& p){
    p.GetBody().Accept(*this);
  }

  virtual void Visit(Block const& p){
    for (auto& c : p.statements_) c->Accept(*this);
  }

  virtual void Visit(IfStmt const& p){
    p.GetCond().Accept(*this);
    p.GetThen().Accept(*this);
    if(p.HasElse()) p.GetElse().Accept(*this);
  }

  virtual void Visit(WhileStmt const& p){
    p.GetCond().Accept(*this);
    p.GetBody().Accept(*this);
  }

  virtual void Visit(BinaryOp const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
    unit_.SetNodeAsRval(p);
  }

  virtual void Visit(AssignStmt const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);

    if(not unit_.IsLValue(p.Lhs()))
      unit_.Error(kErr22, p.Lhs().GetLocus());
  }

  virtual void Visit(RefOp const& p){
    p.Rhs().Accept(*this);

    if(not unit_.IsLValue(p.Rhs()))
      unit_.Error(kErr23, p.Rhs().GetLocus());
    unit_.SetNodeAsLval(p);
  }

  virtual void Visit(DerefOp const& p){
    p.Rhs().Accept(*this);
    if(not unit_.IsLValue(p.Rhs()))
      unit_.Error(kErr24, p.Rhs().GetLocus());
    unit_.SetNodeAsLval(p);
  }

  virtual void Visit(Literal const& p){unit_.SetNodeAsRval(p);}

  virtual void Visit(Var const& p){
    unit_.SetNodeAsLval(p);
  }

  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}
  virtual void Visit(FuncCall const& p){}
  virtual void Visit(FuncRet const& p){}


private:
  CompilationUnit&  unit_;
};


}//end namespace AST
}//end namespace Compiler
