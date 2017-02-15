#include "ASTVisitorPrettyPrinter.hpp"

namespace Compiler{
namespace AST{

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(Block const& p) {
  for (auto c : p.statements){
      c->Accept(*this);
      std::cout << std::endl;Indent();
  }
}  


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(ExprStmt const& p){
  p.GetExpr()->Accept(*this);
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(IfStmt const& p){
  
  std::cout << "if(";
  p.GetCond()->Accept(*this);
  std::cout << "){\n";
  IncreaseIndent();
  Indent();
  p.GetThen()->Accept(*this);
  DecreaseIndent();  
  std::cout << "}";
  
  if(p.HasElse()){
    std::cout << "\nelse{\n";
    IncreaseIndent();
    Indent();
    p.GetElse()->Accept(*this);
    DecreaseIndent();  
    std::cout << "}";    
  }
}


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(Literal const& p){
  std::cout << p.value;
}



/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(BinaryOp const& p){
  std::cout << "( ";
  p.lhs->Accept(*this);
  std::cout << p.OpString();
  p.rhs->Accept(*this);   
  std::cout << " )";
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(DeclStmt const& p){
  p.GetVarDeclList()->Accept(*this);
}
void ASTVisitorPrettyPrinter::Visit(VarDeclList const& p){
  for(const auto it : p.GetVarDeclVector()){
    Indent();
    it->Accept(*this);
    std::cout << " ";
  }
}
void ASTVisitorPrettyPrinter::Visit(VarDecl const& p){
  std::cout << p.str();
}

void ASTVisitorPrettyPrinter::Visit(AssignStmt const& p){
  p.GetLhs()->Accept(*this);
  std::cout << "=";
  p.GetRhs()->Accept(*this);
}

void ASTVisitorPrettyPrinter::Visit(Var const& p){
  std::cout << p.str();
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
