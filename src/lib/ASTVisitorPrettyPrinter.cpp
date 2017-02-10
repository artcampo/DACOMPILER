#include "ASTVisitorPrettyPrinter.hpp"

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(Block const& p) {
  for (auto c : p.statements){
      c->Accept(*this);
      std::cout << std::endl;Indent();
  }
}  


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(ExpressionStatement const& p){
  p.expression->Accept(*this);
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorPrettyPrinter::Visit(StmtIf const& p){
  
  std::cout << "if(";
  p.condition_->Accept(*this);
  std::cout << "){\n";
  IncreaseIndent();
  Indent();
  p.block1_->Accept(*this);
  DecreaseIndent();  
  std::cout << "}";
  
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

void ASTVisitorPrettyPrinter::Indent(){
  for(int i = 0; i < indent_; ++i) std::cout<< " ";
}

void ASTVisitorPrettyPrinter::IncreaseIndent(){
  indent_ += 2;
}
void ASTVisitorPrettyPrinter::DecreaseIndent(){
  if(indent_ > 2) indent_ -= 2;
}
