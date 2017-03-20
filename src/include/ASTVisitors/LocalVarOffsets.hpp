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

//This visitor is only instantiated on functions, not on Prog

class LocalVarOffsets : public ASTVisitor{
public:

  LocalVarOffsets(CompilationUnit& unit, Function& func)
    : unit_(unit), func_(func), offset_(0){};



  virtual void Visit(FuncDef const& p){
//     std::cout << "Local offset\n";
    p.GetBody().Accept(*this);
    IR::AddrOffset k = p.NumPars() - 1;
    IR::AddrOffset i = 0;
    //for(auto& it = p.ParBegin(), end = p.ParEnd(); it != end; ++it){
    for(auto& it : p.ParList()){
      Symbols::Symbol& s = func_.GetSymbolDecl(*it);
      IR::AddrOffset offset    = -2 - (k - i);
      func_.StoreSymbolOffset( s.Id(), IR::Offset(offset, s.BareName()));
//       std::cout << s.str() << " to offset: " << offset << std::endl;
    }
  }

  virtual void Visit(VarDecl const& p){
//     std::cout << p.str() << " to offset: " << offset_ << std::endl;
    Symbols::Symbol& s = func_.GetSymbolDecl(p);
//     std::cout << s.str() << std::endl;
    func_.StoreSymbolOffset( s.Id(), IR::Offset(offset_, s.BareName()));
    offset_ += func_.GetSymbolDecl(p).Size();
//     offset_
  };

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

  //Traversal
  virtual void Visit(WhileStmt const& p){
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
  virtual void Visit(ClassDef const& p){ for(const auto& it : p) it->Accept(*this); }

  //Nothing to do
  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};
  virtual void Visit(ProgBody const& p){};
  virtual void Visit(BinaryOp const& p){};
  virtual void Visit(AssignStmt const& p){};
  virtual void Visit(Literal const& p){};
  virtual void Visit(Var& p)    {};
  virtual void Visit(RefOp const& p){};
  virtual void Visit(DerefOp const& p){};
  virtual void Visit(FuncCall& p){}
  virtual void Visit(FuncRet& p){}
  virtual void Visit(ReturnStmt const& p){}
  virtual void Visit(VarName const& p){}
  virtual void Visit(DotOp const& p){}

private:
  CompilationUnit&  unit_;
  Function&         func_;
  IR::AddrOffset    offset_;
};


}//end namespace AST
}//end namespace Compiler
