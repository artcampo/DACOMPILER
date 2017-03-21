#pragma once
#include "Symbol.hpp"
#include "AST/ASTVisitor.hpp"
#include "AST/Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{
namespace Visitor{

using namespace Symbols;

class ResolveMemberTypes : public ASTVisitor{
public:

  ResolveMemberTypes(CompilationUnit& unit)
    : unit_(unit){};

  //SDD
  virtual void Visit(ClassDef const& p){
    member_scope_id_inht_ =
      unit_.GetClass( p.Name() ).GetHScope().GetScopeId();
    for(const auto& it : p) it->Accept(*this);
  }

  virtual void Visit(Var& p){
//     std::cout << "may patch: " <<  p.str() << "\n";
    if(p.Id() == Symbol::UnknownSymbol()){
//       std::cout << "Patching : " << p.str() << "\n";
      if(not unit_.HasDecl(p.Name(), member_scope_id_inht_)){
        p.SetType (unit_.GetTypeError());
        unit_.Error(kErr91, p.GetLocus());
        return;
      }
      p.SetType (unit_.GetType(p.Name(), member_scope_id_inht_));
      p.SetId   (unit_.DeclId (p.Name(), member_scope_id_inht_));
    }
  }


  //Traversal
  virtual void Visit(ProgBody const& p){
//     std::cout << "may patch: " <<  p.str() << "\n";
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
  virtual void Visit(FuncCall& p){
    p.Receiver().Accept(*this);
    for(const auto& it : p) it->Accept(*this);
  }
  virtual void Visit(DotOp const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
  }

  virtual void Visit(ReturnStmt const& p){p.RetExpr().Accept(*this);}
  virtual void Visit(FuncDef const& p){p.GetBody().Accept(*this);}
  virtual void Visit(RefOp const& p){p.Rhs().Accept(*this);}
  virtual void Visit(DerefOp const& p){p.Rhs().Accept(*this);}
  virtual void Visit(FuncRet& p){ p.GetCall().Accept(*this); }


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

  ScopeId member_scope_id_inht_;
};



}//end namespace Visitor
}//end namespace AST
}//end namespace Compiler
