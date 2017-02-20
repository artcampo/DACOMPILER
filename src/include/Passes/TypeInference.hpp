#pragma once
#include "Passes/Pass.hpp"
#include "ASTVisitor.hpp"

namespace Compiler{

using namespace AST;

class ASTVisitorTypeInference : public ASTVisitor{
public:

  ASTVisitorTypeInference(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(Prog const& p){};
  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(Block const& p){
    for (auto c : p.statements) c->Accept(*this);
  };
  virtual void Visit(IfStmt const& p){
    p.GetCond()->Accept(*this);
    p.GetThen()->Accept(*this);
    if(p.HasElse()) p.GetElse()->Accept(*this);
  };

  virtual void Visit(BinaryOp const& p){
    p.Lhs()->Accept(*this);
    p.Rhs()->Accept(*this);
    if(unit_.GetTypeId(p.Lhs()) == unit_.GetTypeId(p.Rhs()))
      unit_.RecordType(&p, unit_.GetTypeId(p.Lhs()));
    else
      unit_.Error("[err:17] Incompatible types in op", p.GetLocus());
  };
  virtual void Visit(AssignStmt const& p){
    p.Lhs()->Accept(*this);
    p.Rhs()->Accept(*this);
    if(unit_.GetTypeId(p.Lhs()) == unit_.GetTypeId(p.Rhs()))
      unit_.RecordType(&p, unit_.GetTypeId(p.Lhs()));
    else
      unit_.Error("[err:18] Incompatible types in assignment", p.GetLocus());
  };

  virtual void Visit(Literal const& p){unit_.RecordType(&p, p.GetTypeId());};
  virtual void Visit(Var const& p)    {unit_.RecordType(&p, p.GetTypeId());};
  virtual void Visit(DeclStmt const& p){};
  virtual void Visit(VarDeclList const& p){};
  virtual void Visit(VarDecl const& p){};

private:
  CompilationUnit&  unit_;
};

class TypeInference : public Pass{
public:
  TypeInference(CompilationUnit& unit) : Pass(unit){};

  virtual void Run(){
    ASTVisitorTypeInference v(unit_);
    v.Visit(*unit_.ast_.block_);
  };
protected:

};


}//end namespace Compiler
