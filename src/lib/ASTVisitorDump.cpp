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
void ASTVisitorDump::Visit(ExpressionStatement const& p){
//   std::cout << "StmtExpr:\n";
  p.expression->Accept(*this);
  
}



/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(Literal const& p){
  std::cout << "Literal: ";
  std::cout << p.value;
}



/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(BinaryOp const& p){
  std::cout << "Op:" << p.OpString()<<"\n";
  IncreaseIndent(); 
  Indent();
  p.lhs->Accept(*this);
  std::cout << "\n";
  Indent();
  p.rhs->Accept(*this);   
  DecreaseIndent(); 
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(StmtIf const& p){
  std::cout << "StmtIf:\n";
  
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
