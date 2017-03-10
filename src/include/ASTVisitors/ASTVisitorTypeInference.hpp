#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{

class ASTVisitorTypeInference : public ASTVisitor{
public:

  ASTVisitorTypeInference(CompilationUnit& unit): unit_(unit){};


  virtual void Visit(IfStmt const& p){
    p.GetCond().Accept(*this);
    p.GetThen().Accept(*this);
    if(p.HasElse()) p.GetElse().Accept(*this);

    if(not unit_.GetTypeOfNode(p.GetCond()).IsBool())
      unit_.Error(kErr21, p.GetCond().GetLocus());
  }

  virtual void Visit(WhileStmt const& p){
    p.GetCond().Accept(*this);
    p.GetBody().Accept(*this);

    if(not unit_.GetTypeOfNode(p.GetCond()).IsBool())
      unit_.Error(kErr20, p.GetCond().GetLocus());
  }

  virtual void Visit(BinaryOp const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
    if(unit_.GetTypeOfNode(p.Lhs()) != unit_.GetTypeOfNode(p.Rhs()))
      unit_.Error("[err:17] Incompatible types in op", p.GetLocus());
    unit_.SetTypeOfNode(p, unit_.GetTypeOfNode(p.Lhs()));
  }
  virtual void Visit(AssignStmt const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
    if(unit_.GetTypeOfNode(p.Lhs()) != unit_.GetTypeOfNode(p.Rhs()))
      unit_.Error(kErr18
        + unit_.GetTypeOfNode(p.Lhs()).str() + " to "
        + unit_.GetTypeOfNode(p.Rhs()).str(), p.GetLocus());
//     unit_.SetTypeOfNode(&p, unit_.GetTypeOfNode(p.Lhs()));
  }

  //Pre: Lness/Rness of node has been already computed
  virtual void Visit(RefOp const& p){
    p.Rhs().Accept(*this);
    const Type& t = unit_.GetTypeOfNode(p.Rhs());
    unit_.SetTypeOfNode(p, unit_.PtrToT(t) );
  }

  virtual void Visit(DerefOp const& p){
    p.Rhs().Accept(*this);
    const Type& t = unit_.GetTypeOfNode(p.Rhs());

    if(not t.IsPtr()) unit_.Error(kErr25, p.GetLocus());
    else              unit_.SetTypeOfNode(p, unit_.PointedBy(t) );
  }

  virtual void Visit(Literal const& p){unit_.SetTypeOfNode(p, p.GetType());}
  virtual void Visit(Var const& p)    {unit_.SetTypeOfNode(p, p.GetType());}

  virtual void Visit(FuncRet const& p){
    p.GetCall().Accept(*this);
    unit_.SetTypeOfNode(p, p.GetType());
  }

  virtual void Visit(FuncCall const& p){
    unit_.SetTypeOfNode(p, p.GetType());
    const FuncType& ftype = p.GetType();
    const auto& ftype_it  = ftype.cbegin();
    for(const auto& it : p){
      it->Accept(*this);
      if( unit_.GetTypeOfNode(*it) != unit_.GetType(*ftype_it) ){
        unit_.Error(kErr41
          + " is \""      + unit_.GetTypeOfNode(*it).str()
          + "\" but "     + unit_.GetFunc( p.Name() ).str()
          + " expects \"" + unit_.GetType(*ftype_it).str()
          + "\""
          , it->GetLocus());
      }
    }
  }

  virtual void Visit(ReturnStmt const& p){
    p.RetExpr().Accept(*this);
    const Type& rt = p.GetFuncDecl().GetRetType();
    const Type& et = unit_.GetTypeOfNode(p.RetExpr());
    if(rt != et) unit_.Error(kErr45 + rt.str() + " vs " + et.str());
  }

  //Traversal
  virtual void Visit(ProgBody const& p){
    p.GetProgInit().Accept(*this);
    for(auto& it : p) it->Accept(*this);
    for(auto& it : p.GetClassDefs() ) it->Accept(*this);
    p.GetProgEnd().Accept(*this);
  }

  virtual void Visit(FuncDef const& p){
    p.GetBody().Accept(*this);
  }

  virtual void Visit(Block const& p){
    for (auto& c : p.statements_) c->Accept(*this);
  }



  //Nothing to do
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}
  virtual void Visit(ProgInit const& p){}
  virtual void Visit(ProgEnd const& p){}
  virtual void Visit(ClassDef const& p){}
  virtual void Visit(VarName const& p){}

private:
  CompilationUnit&  unit_;
};

}//end namespace AST
}//end namespace Compiler
