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
    std::cout << "Local offset\n";
    p.GetBody().Accept(*this);
  }

  virtual void Visit(Block const& p){
    for(auto& c : p.statements_) c->Accept(*this);
  };

  virtual void Visit(VarDecl const& p){

    std::cout << p.str() << " to offset: " << offset_ << std::endl;
    Symbols::Symbol& s = func_.GetSymbolDecl(p);
    std::cout << s.str() << std::endl;
    offset_ += func_.GetSymbolDecl(p).Size();
//     offset_
  };

  virtual void Visit(WhileStmt const& p){
    p.GetBody().Accept(*this);
  }
  virtual void Visit(DeclStmt const& p){
    p.GetVarDeclList().Accept(*this);
  }

  virtual void Visit(VarDeclList const& p){
    for(auto& it : p) it->Accept(*this);
  }

  virtual void Visit(IfStmt const& p){
//     std::cout << unit_.GetScope(p.GetThen()->GetScopeId())->str() <<"\n";

    IR::Addr start_offset = offset_;
    p.GetThen().Accept(*this);

    if(p.HasElse()){
      IR::Addr then_offset = offset_;
      offset_              = start_offset;
      p.GetElse().Accept(*this);
      IR::Addr else_offset = offset_;
      offset_ = std::max<IR::Addr>(then_offset, else_offset);
//       std::cout << unit_.GetScope(p.GetElse()->GetScopeId())->str() <<"\n";
    }
  };




  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(ProgBody const& p){};

  virtual void Visit(BinaryOp const& p){};
  virtual void Visit(AssignStmt const& p){};
  virtual void Visit(Literal const& p){};
  virtual void Visit(Var const& p)    {};
  virtual void Visit(RefOp const& p){};
  virtual void Visit(DerefOp const& p){};

private:
  CompilationUnit&  unit_;
  Function&         func_;
  IR::Addr          offset_;
};


}//end namespace AST
}//end namespace Compiler
