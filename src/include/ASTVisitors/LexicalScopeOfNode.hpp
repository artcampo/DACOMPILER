#pragma once
#include "AST/ASTVisitor.hpp"
#include "AST/Node.hpp"
#include "ByteCode.hpp"
#include "Utils.hpp"
#include "Function.hpp"
#include "IR/IRSubtypes.hpp"
#include "IR/Offset.hpp"
#include <map>

namespace Compiler{
namespace AST{
namespace Visitor{

//TODO: now only computed for ClassDef

class LexicalScopeOfNode : public ASTVisitor{
public:

  LexicalScopeOfNode(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(ProgBody const& p){
    p.GetProgInit().Accept(*this);
    lscope_inht_ = &unit_.GetGlobalLexicalScope();
    for(auto& it : p.GetClassDefs() ) it->Accept(*this);
    for(auto& it : p) it->Accept(*this);
    p.GetProgEnd().Accept(*this);
  }

  virtual void Visit(ClassDef const& p){
    unit_.SetLScopeOfNode(p, *lscope_inht_);
    for(const auto& it : p) it->Accept(*this);
  }

  virtual void Visit(FuncDef const& p){
    p.GetBody().Accept(*this);
  }

  virtual void Visit(IfStmt const& p){
    p.GetCond().Accept(*this);
    p.GetThen().Accept(*this);
    if(p.HasElse()) p.GetElse().Accept(*this);
  }

  //Traversal
  virtual void Visit(WhileStmt const& p){
    p.GetCond().Accept(*this);
    p.GetBody().Accept(*this);
  }
  virtual void Visit(DeclStmt const& p){
    p.GetVarDeclList().Accept(*this);
  }
  virtual void Visit(VarDeclList const& p){
    for(auto& it : p) it->Accept(*this);
  }
  virtual void Visit(Block const& p){
    for(auto& c : p.statements_) c->Accept(*this);
  };

  virtual void Visit(BinaryOp const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
  }
  virtual void Visit(AssignStmt const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
  };
  virtual void Visit(FuncCall& p){
    p.Receiver().Accept(*this);
    for(const auto& it : p) it->Accept(*this);
  }
  virtual void Visit(DotOp const& p){
    p.Lhs().Accept(*this);
    p.Rhs().Accept(*this);
  }
  virtual void Visit(FuncRet& p){ p.GetCall().Accept(*this); }
  virtual void Visit(ReturnStmt const& p){ p.RetExpr().Accept(*this); }
  virtual void Visit(RefOp const& p){ p.Rhs().Accept(*this); }
  virtual void Visit(DerefOp const& p){ p.Rhs().Accept(*this); }

  //Nothing to do
  virtual void Visit(ProgInit const& p){}
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(Literal const& p){}
  virtual void Visit(Var& p){}
  virtual void Visit(VarName const& p){}
  virtual void Visit(VarDecl const& p){}

private:
  CompilationUnit&  unit_;
  LexicalScope*     lscope_inht_;
};


}//end namespace Visitor
}//end namespace AST
}//end namespace Compiler
