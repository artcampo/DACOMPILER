#pragma once
#include "Passes/Pass.hpp"
#include "AST/ASTVisitor.hpp"

namespace Compiler{

using namespace AST;

class ASTVisitorUninitalizedVariable : public ASTVisitor{
public:

  ASTVisitorUninitalizedVariable(CompilationUnit& unit): unit_(unit){};


  virtual void Visit(ProgBody const& p){
    p.GetProgInit().Accept(*this);
    p.GetMainFunc().Accept(*this);
    p.GetProgEnd().Accept(*this);
  }

  virtual void Visit(FuncDef const& p){
    p.GetBody().Accept(*this);
  }

  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};

  virtual void Visit(Block const& p){
    for (auto& c : p.statements_) c->Accept(*this);
  };
  virtual void Visit(IfStmt const& p){
    p.GetCond()->Accept(*this);
    p.GetThen()->Accept(*this);
    if(p.HasElse()) p.GetElse()->Accept(*this);
  };

  virtual void Visit(BinaryOp const& p){
    p.Lhs()->Accept(*this);
    p.Rhs()->Accept(*this);

  };
  virtual void Visit(AssignStmt const& p){
    p.Lhs()->Accept(*this);
    p.Rhs()->Accept(*this);

  };

  virtual void Visit(Literal const& p){unit_.SetTypeOfNode(p, p.GetType());};
  virtual void Visit(Var& p)    {unit_.SetTypeOfNode(p, p.GetType());};
  virtual void Visit(DeclStmt const& p){};
  virtual void Visit(VarDeclList const& p){};
  virtual void Visit(VarDecl const& p){};

private:
  CompilationUnit&  unit_;
  std::vector<>
};

class UninitalizedVariable : public Pass{
public:
  TypeInference(CompilationUnit& unit) : Pass(unit){};

  virtual void Run(){
    if(unit_.ValidAst()){
      Visitor::ASTVisitorUninitalizedVariable v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };
protected:

};


}//end namespace Compiler
