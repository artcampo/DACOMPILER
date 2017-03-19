#pragma once
#include "AST/ASTVisitor.hpp"
#include "AST/Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{
namespace Visitor{

class TypeCheck : public ASTVisitor{
public:

  TypeCheck(CompilationUnit& unit): unit_(unit){};


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
  }

  virtual void Visit(DerefOp const& p){
    p.Rhs().Accept(*this);
    const Type& t = unit_.GetTypeOfNode(p.Rhs());

    if(not t.IsPtr()) unit_.Error(kErr25, p.GetLocus());

  }

  virtual void Visit(Literal const& p){}
  virtual void Visit(Var& p){}

  virtual void Visit(FuncRet& p){
    p.GetCall().Accept(*this);
  }

  virtual void Visit(FuncCall& p){
    const FuncType& ftype = p.GetType();
    const auto& ftype_it  = ftype.cbegin();
    for(const auto& it : p){
      it->Accept(*this);
      if( unit_.GetTypeOfNode(*it) != unit_.GetType(*ftype_it) )
        unit_.Error(kErr41
          + " is \""      + unit_.GetTypeOfNode(*it).str()
          + "\" but "     + unit_.GetFunc( p.Name() ).str()
          + " expects \"" + unit_.GetType(*ftype_it).str()
          + "\""
          , it->GetLocus());
    }
  }

  virtual void Visit(ReturnStmt const& p){
    p.RetExpr().Accept(*this);
    const Type& rt = p.GetFuncDecl().GetRetType();
    const Type& et = unit_.GetTypeOfNode(p.RetExpr());
    if(rt != et) unit_.Error(kErr45 + rt.str() + " vs " + et.str(), p.GetLocus());
  }

  virtual void Visit(DotOp const& p){
    p.Lhs().Accept(*this);
    const Type& lhs_type = unit_.GetTypeOfNode(p.Lhs());
    if(not lhs_type.IsClass()){
      unit_.Error(kErr89 + lhs_type.str(), p.GetLocus());
      return;
    }
    HierarchicalScope& s = unit_.GetHScope(lhs_type);
    std::string name = p.Rhs().Name();
    if(not s.HasDecl(name)){
      unit_.Error(kErr91 + name + " in expression: " + p.Lhs().str(), p.GetLocus());
      return;
    }
    //const Type& dotop_type = s.GetType(name);
  };

  //Traversal
  virtual void Visit(ProgBody const& p){
    p.GetProgInit().Accept(*this);
    for(auto& it : p.GetClassDefs() ) it->Accept(*this);
    for(auto& it : p) it->Accept(*this);
    p.GetProgEnd().Accept(*this);
  }

  virtual void Visit(FuncDef const& p){
    p.GetBody().Accept(*this);
  }

  virtual void Visit(Block const& p){
    for (auto& c : p.statements_) c->Accept(*this);
  }

  virtual void Visit(ClassDef const& p){ for(const auto& it : p) it->Accept(*this); }


  //Nothing to do
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}
  virtual void Visit(ProgInit const& p){}
  virtual void Visit(ProgEnd const& p){}
  virtual void Visit(VarName const& p){}

private:
  CompilationUnit&  unit_;
};

}//end namespace Visitor
}//end namespace AST
}//end namespace Compiler
