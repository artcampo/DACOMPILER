#pragma once
#include "Passes/Pass.hpp"
#include "ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"

namespace Compiler{

using namespace AST;

class ASTVisitorTypeInference : public ASTVisitor{
public:

  ASTVisitorTypeInference(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(ProgBody const& p){
    p.GetProgInit().Accept(*this);
    p.GetBlock().Accept(*this);
    p.GetProgEnd().Accept(*this);
  }

  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};

  virtual void Visit(Block const& p){
    for (auto& c : p.statements_) c->Accept(*this);
  }
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
      unit_.Error("[err:18] Incompatible types in assignment", p.GetLocus());
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
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}

private:
  CompilationUnit&  unit_;
};

class TypeInference : public Pass{
public:
  TypeInference(CompilationUnit& unit)
    : Pass(unit
        , {CompUnitInfo::kAst, CompUnitInfo::kLnessRnessOfNode}
        , {CompUnitInfo::kTypeOfNode}){};

  virtual void Run(){
    if(unit_.ValidAst()){
      ASTVisitorTypeInference v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("Type inference");
  };

};


}//end namespace Compiler
