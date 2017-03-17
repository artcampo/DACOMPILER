#pragma once
#include "AST/ASTVisitor.hpp"
#include "AST/Node.hpp"
#include "ByteCode.hpp"
#include "Utils.hpp"
#include <map>

namespace Compiler{
namespace AST{

class Scopes : public ASTVisitor{
public:

  Scopes(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(ProgBody const& p){
    std::cout << "\nScopes of module:\n";
    std::cout << unit_.GetScope(
        unit_.GlobalScopeId( unit_.GlobalScopeOwnerId() )
      )->str() <<"\n";
    p.GetProgInit().Accept(*this);
    for(auto& it : p.GetClassDefs() ) it->Accept(*this);
    for(auto& it : p) it->Accept(*this);
    p.GetProgEnd().Accept(*this);
  };

  virtual void Visit(Block const& p){
    std::cout << unit_.GetScope(p.GetScopeId())->str() <<"\n";
    for(auto& c : p.statements_) c->Accept(*this);
  };

  virtual void Visit(ClassDef const& p){
    std::cout << unit_.GetClass(p.Name()).GetHScope().str() << "\n";
    for(const auto& it : p) it->Accept(*this);
  }

  //Traversal
  virtual void Visit(FuncDef const& p){
    p.GetBody().Accept(*this);
  }


  virtual void Visit(IfStmt const& p){
//     std::cout << unit_.GetScope(p.GetThen()->GetScopeId())->str() <<"\n";
    p.GetThen().Accept(*this);

    if(p.HasElse()){
      p.GetElse().Accept(*this);
//       std::cout << unit_.GetScope(p.GetElse()->GetScopeId())->str() <<"\n";
    }
  };

  virtual void Visit(WhileStmt const& p){
    p.GetBody().Accept(*this);
  }

  //Nothing to do
  virtual void Visit(BinaryOp const& p){}
  virtual void Visit(AssignStmt const& p){}
  virtual void Visit(Literal const& p){}
  virtual void Visit(Var& p)    {}
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}
  virtual void Visit(RefOp const& p){}
  virtual void Visit(DerefOp const& p){}
  virtual void Visit(ProgInit const& p){}
  virtual void Visit(ProgEnd const& p){}
  virtual void Visit(FuncCall& p){}
  virtual void Visit(FuncRet& p){}
  virtual void Visit(ReturnStmt const& p){}
  virtual void Visit(VarName const& p){}
  virtual void Visit(DotOp const& p){};

private:
  CompilationUnit&  unit_;
};


}//end namespace AST
}//end namespace Compiler
