#include "ASTVisitors/ASTVisitorPrettyPrinter.hpp"

namespace Compiler{
namespace AST{

void ASTVisitorPrettyPrinter::Visit(ProgBody const& p){
  p.GetProgInit().Accept(*this);
  for(auto& it : p) it->Accept(*this);
  p.GetProgEnd().Accept(*this);
}

void ASTVisitorPrettyPrinter::Visit(FuncDef const& p){
  p.GetBody().Accept(*this);
}

void ASTVisitorPrettyPrinter::Visit(ProgInit const& p){


}
void ASTVisitorPrettyPrinter::Visit(ProgEnd const& p){

}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(Block const& p) {
  for (auto& c : p.statements_){
      c->Accept(*this);
      std::cout << std::endl;Indent();
  }
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(IfStmt const& p){

  std::cout << "if(";
  p.GetCond().Accept(*this);
  std::cout << "){\n";
  IncreaseIndent();
  Indent();
  p.GetThen().Accept(*this);
  DecreaseIndent();
  std::cout << "}";

  if(p.HasElse()){
    std::cout << "\nelse{\n";
    IncreaseIndent();
    Indent();
    p.GetElse().Accept(*this);
    DecreaseIndent();
    std::cout << "}";
  }
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(WhileStmt const& p){
  std::cout << "while("; p.GetCond().Accept(*this);
  std::cout << "){\n";
  IncreaseIndent(); Indent(); p.GetBody().Accept(*this);DecreaseIndent();
  std::cout << "}";
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(Literal const& p){
  std::cout << p.Value();
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(BinaryOp const& p){
  std::cout << "( ";
  p.Lhs().Accept(*this);
  std::cout << p.OpString();
  p.Rhs().Accept(*this);
  std::cout << " )";
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(DeclStmt const& p){
  p.GetVarDeclList().Accept(*this);
}
void ASTVisitorPrettyPrinter::Visit(VarDeclList const& p){
  for(const auto& it : p.GetVarDeclVector()){
    it->Accept(*this);
    std::cout << " ";
  }
}
void ASTVisitorPrettyPrinter::Visit(VarDecl const& p){
  std::cout << p.str();
}

void ASTVisitorPrettyPrinter::Visit(AssignStmt const& p){
  p.Lhs().Accept(*this);
  std::cout << "=";
  p.Rhs().Accept(*this);
}

void ASTVisitorPrettyPrinter::Visit(Var const& p){
  std::cout << p.str();
}

void ASTVisitorPrettyPrinter::Visit(RefOp const& p){
  std::cout << p.str();
  p.Rhs().Accept(*this);

}

void ASTVisitorPrettyPrinter::Visit(DerefOp const& p){
  std::cout << p.str();
  p.Rhs().Accept(*this);
}

void ASTVisitorPrettyPrinter::Visit(FuncCall const& p){
  p.str();
  for(const auto& it : p) it->Accept(*this);
}
void ASTVisitorPrettyPrinter::Visit(FuncRet const& p){
  p.GetCall().Accept(*this);
}

void ASTVisitorPrettyPrinter::Visit(ReturnStmt const& p){
  std::cout << p.str(); std::cout << "\n";
  IncreaseIndent(); Indent(); p.RetExpr().Accept(*this); DecreaseIndent();
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Indent(){
  for(int i = 0; i < indent_; ++i) std::cout<< " ";
}

void ASTVisitorPrettyPrinter::IncreaseIndent(){
  indent_ += 2;
}
void ASTVisitorPrettyPrinter::DecreaseIndent(){
  if(indent_ >= 2) indent_ -= 2;
}

}//end namespace AST
}//end namespace Compiler
