#pragma once
#include "AST/ASTVisitor.hpp"
#include "AST/Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{
namespace Visitor{

class VarIsValueOrAddress : public ASTVisitor{
public:

  VarIsValueOrAddress(CompilationUnit& unit)
    : unit_(unit)
    , is_val_or_addr_inht_(true){};

  //SDD
  virtual void Visit(RefOp const& p){
    is_val_or_addr_inht_ = false;
    p.Rhs().Accept(*this);
    is_val_or_addr_inht_ = true;
  }

  virtual void Visit(Var& p){
    if(is_val_or_addr_inht_)
      unit_.SetVarUsageAsValue(p);
    else{
      unit_.SetVarUsageAsAddress(p);
      is_val_or_addr_inht_ = true;
    }
  }

  virtual void Visit(DotOp const& p){
    is_val_or_addr_inht_ = false;
    p.Lhs().Accept(*this);
    is_val_or_addr_inht_ = true;
  }

  //Traversal
  virtual void Visit(ProgBody const& p){
    p.GetProgInit().Accept(*this);
    for(auto& it : p.GetClassDefs() ) it->Accept(*this);
    for(auto& it : p) it->Accept(*this);
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
  virtual void Visit(FuncCall& p) {
    p.Receiver().Accept(*this);
    for(const auto& it : p) it->Accept(*this);
  }

  virtual void Visit(ReturnStmt const& p){
    p.RetExpr().Accept(*this);
  }

  virtual void Visit(FuncDef const& p){p.GetBody().Accept(*this);}
  virtual void Visit(DerefOp const& p){p.Rhs().Accept(*this);}
  virtual void Visit(FuncRet& p){ p.GetCall().Accept(*this); }
  virtual void Visit(ClassDef const& p){ for(const auto& it : p) it->Accept(*this); }


  //Nothing to do
  virtual void Visit(Literal const& p){}
  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}
  virtual void Visit(VarName const& p){}



private:
  CompilationUnit&  unit_;
  bool              is_val_or_addr_inht_;
};



}//end namespace Visitor
}//end namespace AST
}//end namespace Compiler
