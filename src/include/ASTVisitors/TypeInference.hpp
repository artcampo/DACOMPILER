#pragma once
#include "AST/ASTVisitor.hpp"
#include "AST/Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{
namespace Visitor{

class TypeInference : public ASTVisitor{
public:

  TypeInference(CompilationUnit& unit): unit_(unit){};


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
    unit_.SetTypeOfNode(p, unit_.GetTypeOfNode(p.Lhs()));
  }
  virtual void Visit(AssignStmt const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
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

    if(not t.IsPtr()) unit_.SetTypeOfNode(p, unit_.GetTypeError() );
    else              unit_.SetTypeOfNode(p, unit_.PointedBy(t) );
  }

  virtual void Visit(Literal const& p){unit_.SetTypeOfNode(p, p.GetType());}
  virtual void Visit(Var& p)    {
//     std::cout << "set " << p.str() << " to " << p.GetType().str() << "\n";
    unit_.SetTypeOfNode(p, p.GetType());}

  virtual void Visit(FuncRet& p){
    p.GetCall().Accept(*this);
    unit_.SetTypeOfNode(p, p.GetType());
  }

  virtual void Visit(FuncCall& p){
    unit_.SetTypeOfNode(p, p.GetType());
    const FuncType& ftype = p.GetType();
    const auto& ftype_it  = ftype.cbegin();
    p.Receiver().Accept(*this);
    for(const auto& it : p) it->Accept(*this);
  }

  virtual void Visit(ReturnStmt const& p){
    p.RetExpr().Accept(*this);
  }

  virtual void Visit(DotOp const& p){
    p.Lhs().Accept(*this);
    const Type& lhs_type = unit_.GetTypeOfNode(p.Lhs());
    if(not lhs_type.IsClass()){
      unit_.SetTypeOfNode(p, unit_.GetTypeError());
      return;
    }
    HierarchicalScope& s = unit_.GetHScope(lhs_type);
    std::string name = p.Rhs().Name();
    if(not s.HasDecl(name)){
      unit_.SetTypeOfNode(p, unit_.GetTypeError());
      return;
    }
    const Type& dotop_type = s.GetType(name);
    unit_.SetTypeOfNode(p, dotop_type);
  };

  virtual void Visit(ClassDef const& p){ 
    for(const auto& it : p) it->Accept(*this); 
    const LexicalScope& lscope = unit_.GetLScopeOfNode(p);
    const Type& type = lscope.PostGetType(p.Name());
    unit_.SetTypeOfNode(p, type);
  }  
  
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
