#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{
namespace Visitor{

class VarIsReadOrWrite : public ASTVisitor{
public:

  VarIsReadOrWrite(CompilationUnit& unit)
    : unit_(unit)
    , is_read_or_write_inht_(true){};


  //santa's little helper
  void Set(ExprVar const& p){
    if(is_read_or_write_inht_)  unit_.SetAsRead(p);
    else                        unit_.SetAsWrite(p);
  }

  virtual void Visit(AssignStmt const& p){
    is_read_or_write_inht_ = false; p.Lhs().Accept(*this);
    is_read_or_write_inht_ = true;  p.Rhs().Accept(*this);
  }

  virtual void Visit(DerefOp const& p){
    Set(p);
    p.Rhs().Accept(*this);
    is_read_or_write_inht_ = true;
  }

  virtual void Visit(Var const& p)      { Set(p);}
  virtual void Visit(FuncCall const& p) {
    //TODO: should funcCall be an expression?
    for(const auto& it : p) it->Accept(*this);
  }

  virtual void Visit(ReturnStmt const& p){
    is_read_or_write_inht_ = true;
    p.RetExpr().Accept(*this);
  }
  //SDD

  //Traversal
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
  }

  virtual void Visit(RefOp const& p){
    p.Rhs().Accept(*this);
  }

  virtual void Visit(FuncRet const& p){ p.GetCall().Accept(*this); }

  //Nothing to do
  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}
  virtual void Visit(Literal const& p){}



private:
  CompilationUnit&  unit_;
  bool              is_read_or_write_inht_;
};


}//end namespace Visitor
}//end namespace AST
}//end namespace Compiler
