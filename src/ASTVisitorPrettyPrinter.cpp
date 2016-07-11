#include "ASTVisitorPrettyPrinter.hpp"

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(Block const& p) {
  if (this->ActBefore(p)) { return; }

  for (auto c : p.statements){
      c.Accept(*this);
      std::cout << std::endl;
  }
  
  this->ActAfter(p);
}  

bool ASTVisitorPrettyPrinter::ActBefore(Block const& p){};
void ASTVisitorPrettyPrinter::ActAfter (Block const& p){};

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(ExpressionStatement const& p){
  if (this->ActBefore(p)) { return; }

  p.expression.Accept(*this);
  
  this->ActAfter(p);  
}

bool ASTVisitorPrettyPrinter::ActBefore(ExpressionStatement const& p){};
void ASTVisitorPrettyPrinter::ActAfter (ExpressionStatement const& p){};   

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(Literal const& p){
  if (this->ActBefore(p)) { return; }
  std::cout << p.value;
  this->ActAfter(p);   
}

bool ASTVisitorPrettyPrinter::ActBefore(Literal const& p){};
void ASTVisitorPrettyPrinter::ActAfter (Literal const& p){};     

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(BinaryOp const& p){
  if (this->ActBefore(p)) { return; }

  p.lhs.Accept(*this);
  std::cout << " + ";
  p.rhs.Accept(*this);
  
  this->ActAfter(p);    
}

bool ASTVisitorPrettyPrinter::ActBefore(BinaryOp const& p){};
void ASTVisitorPrettyPrinter::ActAfter (BinaryOp const& p){};   