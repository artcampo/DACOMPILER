#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"
#include "ByteCode.hpp"
#include "Utils.hpp"
#include "Function.hpp"
#include "IR/IRSubtypes.hpp"
#include <map>

namespace Compiler{
namespace AST{

class LocalVarOffsets : public ASTVisitor{
public:

  LocalVarOffsets(CompilationUnit& unit, Function& func)
    : unit_(unit), func_(func), offset_(0){};



  virtual void Visit(FuncDecl const& p){
    p.GetBody().Accept(*this);
  }

  virtual void Visit(Block const& p){
    for(auto& c : p.statements_) c->Accept(*this);
  };

  virtual void Visit(VarDecl const& p){
    std::cout << p.str() << " to offset: " << offset_;
    offset_ += func_.GetSymbolDecl(p).GetSize();
//     offset_

  };

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

  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(ProgBody const& p){};

  virtual void Visit(BinaryOp const& p){};
  virtual void Visit(AssignStmt const& p){};

  virtual void Visit(Literal const& p){};
  virtual void Visit(Var const& p)    {};
  virtual void Visit(DeclStmt const& p){};
  virtual void Visit(VarDeclList const& p){};

  virtual void Visit(RefOp const& p){};
  virtual void Visit(DerefOp const& p){};

private:
  CompilationUnit&  unit_;
  Function&         func_;
  IR::Addr          offset_;
};


}//end namespace AST
}//end namespace Compiler
