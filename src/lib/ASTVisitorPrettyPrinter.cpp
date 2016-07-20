#include "ASTVisitorPrettyPrinter.hpp"

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(Block const& p) {
  for (auto c : p.statements){
      c->Accept(*this);
      std::cout << std::endl;
  }
}  


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(ExpressionStatement const& p){
  p.expression->  Accept(*this);
}


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(Literal const& p){
  std::cout << p.value;
}



/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(BinaryOp const& p){
  p.lhs->Accept(*this);
  std::cout << " + ";
  p.rhs->Accept(*this);   
}
