#pragma once
#include "Passes/Pass.hpp"
#include "ASTVisitor.hpp"

namespace Compiler{

using namespace AST;

class ASTVisitorTypeInference : public ASTVisitor{
public:

  ASTVisitorTypeInference(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(Block const& p){
    for (auto c : p.statements) c->Accept(*this);
  };
  virtual void Visit(IfStmt const& p){
    p.GetCond()->Accept(*this);
    p.GetThen()->Accept(*this);
    if(p.HasElse()) p.GetElse()->Accept(*this);
  };
  virtual void Visit(ExprStmt const& p){};

  virtual void Visit(BinaryOp const& p){
    p.Lhs()->Accept(*this);
    p.Rhs()->Accept(*this);
//     if(unit_.GetType())
  };
  virtual void Visit(DeclStmt const& p){};
  virtual void Visit(VarDeclList const& p){};
  virtual void Visit(VarDecl const& p){};
  virtual void Visit(AssignStmt const& p){};

  virtual void Visit(Literal const& p){unit_.RecordType(&p, p.GetTypeId());};
  virtual void Visit(Var const& p)    {unit_.RecordType(&p, p.GetTypeId());};

private:
  CompilationUnit&  unit_;
};

class TypeInference : public Pass{
public:
  TypeInference(CompilationUnit& unit) : Pass(unit){};

  virtual void Run(){
    ASTVisitorTypeInference v(unit_);
  };
protected:

};


}//end namespace Compiler
