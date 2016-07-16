#include "ASTVisitorCodeGenerator.hpp"

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(Block const& p) {
//   std::cout << "visit on Block\n";
  if (this->ActBefore(p)) { return; }

  for (auto c : p.statements){
      c->Accept(*this);
  }
  
  this->ActAfter(p);
}  

bool ASTVisitorCodeGenerator::ActBefore(Block const& p){return false;};
void ASTVisitorCodeGenerator::ActAfter (Block const& p){};

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(ExpressionStatement const& p){
  if (this->ActBefore(p)) { return; }

  p.expression->  Accept(*this);
  
  this->ActAfter(p);  
}

bool ASTVisitorCodeGenerator::ActBefore(ExpressionStatement const& p){return false;};
void ASTVisitorCodeGenerator::ActAfter (ExpressionStatement const& p){};   

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(Literal const& p){
  if (this->ActBefore(p)) { return; }
  this->ActAfter(p);   
}

bool ASTVisitorCodeGenerator::ActBefore(Literal const& p){ return false;};
void ASTVisitorCodeGenerator::ActAfter (Literal const& p){};     

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(BinaryOp const& p){
  if (this->ActBefore(p)) { return; }

  p.lhs->Accept(*this);
  p.rhs->Accept(*this);
  
  this->ActAfter(p);    
}

bool ASTVisitorCodeGenerator::ActBefore(BinaryOp const& p){return false;};
void ASTVisitorCodeGenerator::ActAfter (BinaryOp const& p){};   