#include "ASTVisitorDump.hpp"

namespace Compiler{
namespace AST{

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(Block const& p) {
//   std::cout << "Stmts:\n";
  for (auto c : p.statements){
      Indent();
      c->Accept(*this);
      std::cout << std::endl;
  }
}


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(ExprStmt const& p){
//   std::cout << "StmtExpr:\n";
  p.GetExpr()->Accept(*this);

}



/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(Literal const& p){
  std::cout << "Literal: ";
  std::cout << p.Value();
}



/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(BinaryOp const& p){
  std::cout << "Op:" << p.OpString()<<"\n";
  IncreaseIndent();
  Indent();
  p.Lhs()->Accept(*this);
  std::cout << "\n";
  Indent();
  p.Rhs()->Accept(*this);
  DecreaseIndent();
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(IfStmt const& p){
  std::cout << "IfStmt:\n";

  IncreaseIndent();
  Indent();std::cout << "Cond: ";

  p.GetCond()->Accept(*this);
  std::cout << "\n";

  Indent();std::cout << "Then:\n";

  IncreaseIndent();
  p.GetThen()->Accept(*this);
  DecreaseIndent();


  if(p.HasElse()){
    Indent();std::cout << "Else:\n";
    IncreaseIndent();
    p.GetElse()->Accept(*this);
    DecreaseIndent();
  }
  DecreaseIndent();
}

void ASTVisitorDump::Visit(DeclStmt const& p){
  p.GetVarDeclList()->Accept(*this);
}
void ASTVisitorDump::Visit(VarDeclList const& p){
  for(const auto it : p.GetVarDeclVector()){
    Indent();
    it->Accept(*this);
    std::cout << " ";
  }
}
void ASTVisitorDump::Visit(VarDecl const& p){
  std::cout << p.str();
}

void ASTVisitorDump::Visit(AssignStmt const& p){
  std::cout << "Assign\n";
  IncreaseIndent();
  Indent(); p.Lhs()->Accept(*this); std::cout << "\n";
  Indent(); p.Rhs()->Accept(*this); std::cout ;
  DecreaseIndent();
}

void ASTVisitorDump::Visit(Var const& p){
  std::cout << p.str();
}


void ASTVisitorDump::Indent(){
  for(int i = 0; i < indent_; ++i) std::cout<< "-";
}

void ASTVisitorDump::IncreaseIndent(){
  indent_ += 1;
}
void ASTVisitorDump::DecreaseIndent(){
  if(indent_ > 0) indent_ -= 1;
}

}//end namespace AST
}//end namespace Compiler
