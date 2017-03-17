#include "ASTVisitors/PrettyPrinter.hpp"

namespace Compiler{
namespace AST{

void PrettyPrinter::Visit(ProgBody const& p){
  p.GetProgInit().Accept(*this);
  for(auto& it : p.GetClassDefs() ) it->Accept(*this);
  for(auto& it : p) it->Accept(*this);
  p.GetProgEnd().Accept(*this);
}

void PrettyPrinter::Visit(FuncDef const& p){
  p.GetBody().Accept(*this);
}

void PrettyPrinter::Visit(ClassDef const& p){
  std::cout << p.str();
}

void PrettyPrinter::Visit(ProgInit const& p){


}
void PrettyPrinter::Visit(ProgEnd const& p){

}

/////////////////////////////////////////////////////////////////////////////
void PrettyPrinter::Visit(Block const& p) {
  for (auto& c : p.statements_){
      c->Accept(*this);
      std::cout << std::endl;Indent();
  }
}

/////////////////////////////////////////////////////////////////////////////
void PrettyPrinter::Visit(IfStmt const& p){

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
void PrettyPrinter::Visit(WhileStmt const& p){
  std::cout << "while("; p.GetCond().Accept(*this);
  std::cout << "){\n";
  IncreaseIndent(); Indent(); p.GetBody().Accept(*this);DecreaseIndent();
  std::cout << "}";
}

/////////////////////////////////////////////////////////////////////////////
void PrettyPrinter::Visit(Literal const& p){
  std::cout << p.Value();
}

/////////////////////////////////////////////////////////////////////////////
void PrettyPrinter::Visit(BinaryOp const& p){
  std::cout << "( ";
  p.Lhs().Accept(*this);
  std::cout << p.OpString();
  p.Rhs().Accept(*this);
  std::cout << " )";
}

/////////////////////////////////////////////////////////////////////////////
void PrettyPrinter::Visit(DeclStmt const& p){
  p.GetVarDeclList().Accept(*this);
}
void PrettyPrinter::Visit(VarDeclList const& p){
  for(const auto& it : p.GetVarDeclVector()){
    it->Accept(*this);
    std::cout << " ";
  }
}
void PrettyPrinter::Visit(VarDecl const& p){
  std::cout << p.str();
}

void PrettyPrinter::Visit(AssignStmt const& p){
  p.Lhs().Accept(*this);
  std::cout << "=";
  p.Rhs().Accept(*this);
}

void PrettyPrinter::Visit(Var& p){
  std::cout << p.str();
}

void PrettyPrinter::Visit(RefOp const& p){
  std::cout << p.str();
  p.Rhs().Accept(*this);

}

void PrettyPrinter::Visit(DerefOp const& p){
  std::cout << p.str();
  p.Rhs().Accept(*this);
}

void PrettyPrinter::Visit(FuncCall& p){
  p.str();
  for(const auto& it : p) it->Accept(*this);
}
void PrettyPrinter::Visit(FuncRet& p){
  p.GetCall().Accept(*this);
}

void PrettyPrinter::Visit(ReturnStmt const& p){
  std::cout << p.str(); std::cout << "\n";
  IncreaseIndent(); Indent(); p.RetExpr().Accept(*this); DecreaseIndent();
}

void PrettyPrinter::Visit(VarName const& p){
  std::cout << p.str();
}

void PrettyPrinter::Visit(DotOp const& p){
  std::cout << p.str(); std::cout << "\n";
  IncreaseIndent(); Indent(); p.Lhs().Accept(*this); DecreaseIndent();
  IncreaseIndent(); Indent(); p.Rhs().Accept(*this); DecreaseIndent();
}


/////////////////////////////////////////////////////////////////////////////
void PrettyPrinter::Indent(){
  for(int i = 0; i < indent_; ++i) std::cout<< " ";
}

void PrettyPrinter::IncreaseIndent(){
  indent_ += 2;
}
void PrettyPrinter::DecreaseIndent(){
  if(indent_ >= 2) indent_ -= 2;
}

}//end namespace AST
}//end namespace Compiler
