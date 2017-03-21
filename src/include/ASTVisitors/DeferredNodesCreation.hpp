#pragma once
#include "AST/ASTVisitor.hpp"
#include "AST/Node.hpp"
#include "CompilationUnit.hpp"
#include "ErrorLog/Messages.hpp"
#include "ASTVisitors/TypeInference.hpp"

namespace Compiler{
namespace AST{
namespace Visitor{

class DeferredNodesCreation : public ASTVisitor{
public:

  DeferredNodesCreation(CompilationUnit& unit
  , TypeInference& type_inf_visitor)
    : unit_(unit), type_inf_visitor_(type_inf_visitor){};

  //SDD
  virtual void Visit(FuncRet& p){
    p.GetCall().Accept(*this); if(unit_.HasErrors()) return;


    const Type& type = unit_.GetTypeOfNode(p.GetCall());
    const AST::FuncType& type_func = dynamic_cast<const AST::FuncType&>(type);
    const Type& type_ret = unit_.GetType(type_func.RetTypeId());
    p.SetType(type_ret);
  }

  virtual void Visit(FuncCall& p){
    p.Receiver().Accept(type_inf_visitor_);

    const Type& type = unit_.GetTypeOfNode(p.Receiver());

    if(not type.IsFunc()) { unit_.Error(kErr38, p.GetLocus()); return;}

    const AST::FuncType& type_func = dynamic_cast<const AST::FuncType&>(type);

    if(p.NumArgs() < type_func.NumPars()){ unit_.Error(kErr39, p.GetLocus()); return;}
    if(p.NumArgs() > type_func.NumPars()){ unit_.Error(kErr40, p.GetLocus()); return;}

    p.SetType(type_func);
    unit_.SetTypeOfNode(p, type_func);

    p.Receiver().Accept(*this);
    for(const auto& it : p) it->Accept(*this);
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

  virtual void Visit(ReturnStmt const& p){
    p.RetExpr().Accept(*this);
  }

  virtual void Visit(FuncDef const& p){p.GetBody().Accept(*this);}
  virtual void Visit(DerefOp const& p){p.Rhs().Accept(*this);}
  virtual void Visit(RefOp const& p){p.Rhs().Accept(*this);}
  virtual void Visit(ClassDef const& p){ for(const auto& it : p) it->Accept(*this); }
  virtual void Visit(DotOp const& p){ p.Lhs().Accept(*this); }


  //Nothing to do
  virtual void Visit(Literal const& p){}
  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}
  virtual void Visit(VarName const& p){}
  virtual void Visit(Var& p){}


private:
  CompilationUnit&  unit_;
  TypeInference& type_inf_visitor_;
};



}//end namespace Visitor
}//end namespace AST
}//end namespace Compiler
