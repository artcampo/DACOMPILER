#include "ASTVisitorCodeGenerator.hpp"
#include "IRBuilder.hpp"
#include "Utils.hpp"

namespace Compiler{
namespace AST{

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(Block const& n) {
  for (auto c : n.statements){
      c->Accept(*this);
  }
}  


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(ExprStmt const& n){
  n.GetExpr()->Accept(*this);
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(IfStmt const& p){
  //TODO
//   p.Expr->Accept(*this);
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(Literal const& n){
  const uint32_t reg_assigned = reg_allocator_.freeRegister();
  reg_of_Expr_[&n]      = reg_assigned;
  byte_code_.stream.push_back( IRBuilder::Load(reg_assigned, n.value) );
}


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(BinaryOp const& n){
  n.lhs->Accept(*this);
  n.rhs->Accept(*this);
  
  const uint32_t reg_assigned = reg_allocator_.freeRegister();
  reg_of_Expr_[&n]      = reg_assigned;
  const uint32_t reg_src1     = reg_of_Expr_[n.lhs];
  const uint32_t reg_src2     = reg_of_Expr_[n.rhs];
  const uint32_t op           = n.op;
  byte_code_.stream.push_back( IRBuilder::Arith(reg_src1, reg_src2, 
                                                reg_assigned, op));
//   std::cout << "OP: " << op << "\n";
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Print() const{
  VMUtils::print(byte_code_);
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::EndOfProgram(){
  byte_code_.stream.push_back( IRBuilder::Stop());
}

}//end namespace AST
}//end namespace Compiler
