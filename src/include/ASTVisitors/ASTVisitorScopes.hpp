#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"
#include "ByteCode.hpp"
#include "Utils.hpp"
#include <map>

namespace Compiler{
namespace AST{

class ASTVisitorScopes : public ASTVisitor{
public:

  ASTVisitorScopes(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(ProgBody const& p){
    std::cout << "\nScopes of module:\n";
    std::cout << unit_.GetScope(
        unit_.GlobalScopeId( unit_.GlobalScopeOwnerId() )
      )->str() <<"\n";
    p.GetProgInit().Accept(*this);
    for(auto& it : p) it->Accept(*this);
    p.GetProgEnd().Accept(*this);
  };

  virtual void Visit(Block const& p){
    std::cout << unit_.GetScope(p.GetScopeId())->str() <<"\n";
    for(auto& c : p.statements_) c->Accept(*this);
  };

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
  virtual void Visit(BinaryOp const& p){};
  virtual void Visit(AssignStmt const& p){};
  virtual void Visit(Literal const& p){};
  virtual void Visit(Var const& p)    {};
  virtual void Visit(DeclStmt const& p){};
  virtual void Visit(VarDeclList const& p){};
  virtual void Visit(VarDecl const& p){};
  virtual void Visit(RefOp const& p){};
  virtual void Visit(DerefOp const& p){};
  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(FuncCall const& p){}
  virtual void Visit(FuncRet const& p){}
  virtual void Visit(ReturnStmt const& p){};

private:
  CompilationUnit&  unit_;
};


}//end namespace AST
}//end namespace Compiler
