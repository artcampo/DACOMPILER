#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{

class VarIsValueOrAddress : public ASTVisitor{
public:

  VarIsValueOrAddress(CompilationUnit& unit)
    : unit_(unit)
    , is_val_or_addr_inht_(true){};



  virtual void Visit(RefOp const& p){
    is_val_or_addr_inht_ = false;
    p.Rhs().Accept(*this);
    is_val_or_addr_inht_ = true;
  }




  virtual void Visit(Var const& p){
    if(is_val_or_addr_inht_)  unit_.SetVarUsageAsValue(p);
    else                      unit_.SetVarUsageAsAddress(p);
  }

  //Traversal
  virtual void Visit(ProgBody const& p){
    p.GetProgInit().Accept(*this);
    p.GetMainFunc().Accept(*this);
    p.GetProgEnd().Accept(*this);
  }

  virtual void Visit(FuncDecl const& p){
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

  virtual void Visit(AssignStmt const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
  }

  virtual void Visit(BinaryOp const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
  }

  virtual void Visit(DerefOp const& p){
    p.Rhs().Accept(*this);
  }

  //Nothing to do
  virtual void Visit(Literal const& p){}
  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}

//   virtual void Visit(UnaryOp const& p){}


private:
  CompilationUnit&  unit_;
  bool              is_val_or_addr_inht_;
};


}//end namespace AST
}//end namespace Compiler
