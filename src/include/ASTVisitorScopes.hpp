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
    p.GetProgInit()->Accept(*this);
    p.GetBlock()->Accept(*this);
    p.GetProgEnd()->Accept(*this);
  };

  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};

  virtual void Visit(Block const& p){
    std::cout << unit_.GetScope(p.GetScopeId())->str() <<"\n";
    for (auto c : p.statements) c->Accept(*this);
  };
  virtual void Visit(IfStmt const& p){
//     std::cout << unit_.GetScope(p.GetThen()->GetScopeId())->str() <<"\n";
    p.GetThen()->Accept(*this);

    if(p.HasElse()){
      p.GetElse()->Accept(*this);
//       std::cout << unit_.GetScope(p.GetElse()->GetScopeId())->str() <<"\n";
    }
  };

  virtual void Visit(WhileStmt const& p){
    p.GetBody()->Accept(*this);
  }

  virtual void Visit(BinaryOp const& p){};
  virtual void Visit(AssignStmt const& p){};

  virtual void Visit(Literal const& p){};
  virtual void Visit(Var const& p)    {};
  virtual void Visit(DeclStmt const& p){};
  virtual void Visit(VarDeclList const& p){};
  virtual void Visit(VarDecl const& p){};
  virtual void Visit(RefOp const& p){};
  virtual void Visit(DerefOp const& p){};

private:
  CompilationUnit&  unit_;
};


}//end namespace AST
}//end namespace Compiler
