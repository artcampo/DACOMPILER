#pragma once
#include "AST/ASTVisitor.hpp"
#include "AST/Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{
namespace Visitor{

class ResolveMemberTypes : public ASTVisitor{
public:

  ResolveMemberTypes(CompilationUnit& unit)
    : unit_(unit){};

  //SDD
  virtual void Visit(RefOp const& p){
    p.Rhs().Accept(*this);
  }

  virtual void Visit(Var const& p){
  }

  //Traversal
  virtual void Visit(ProgBody const& p){
    p.GetProgInit().Accept(*this);
    for(auto& it : p) it->Accept(*this);
    for(auto& it : p.GetClassDefs() ) it->Accept(*this);
    p.GetProgEnd().Accept(*this);
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

  virtual void Visit(AssignStmt const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
  }

  virtual void Visit(BinaryOp const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
  }

  virtual void Visit(ReturnStmt const& p){
    p.RetExpr().Accept(*this);
  }

  virtual void Visit(FuncDef const& p){p.GetBody().Accept(*this);}
  virtual void Visit(DerefOp const& p){p.Rhs().Accept(*this);}
  virtual void Visit(FuncRet const& p){ p.GetCall().Accept(*this); }

  virtual void Visit(FuncCall const& p){
    for(const auto& it : p) it->Accept(*this);
  }

  //Nothing to do
  virtual void Visit(Literal const& p){}
  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}
  virtual void Visit(ClassDef const& p){}
  virtual void Visit(VarName const& p){}
  virtual void Visit(DotOp const& p){}


private:
  CompilationUnit&  unit_;
};



}//end namespace Visitor
}//end namespace AST
}//end namespace Compiler
