#pragma once
#include "Passes/Pass.hpp"
#include "ASTVisitor.hpp"

namespace Compiler{

using namespace AST;

class ASTVisitorTypeInference : public ASTVisitor{
public:

  ASTVisitorTypeInference(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(Block const& p){};
  virtual void Visit(IfStmt const& p){};
  virtual void Visit(ExprStmt const& p){};
  virtual void Visit(Literal const& p){};
  virtual void Visit(BinaryOp const& p){};
  virtual void Visit(DeclStmt const& p){};
  virtual void Visit(VarDeclList const& p){};
  virtual void Visit(VarDecl const& p){};
  virtual void Visit(AssignStmt const& p){};
  virtual void Visit(Var const& p){};

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
