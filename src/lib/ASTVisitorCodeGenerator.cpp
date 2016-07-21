#include "ASTVisitorCodeGenerator.hpp"
#include "IRBuilder.hpp"
#include "Utils.hpp"

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(Block const& n) {
  for (auto c : n.statements){
      c->Accept(*this);
  }
}  


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(ExpressionStatement const& n){
  n.expression->Accept(*this);
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(Literal const& n){
  const uint32_t reg_assigned = reg_allocator_.freeRegister();
  reg_of_expression_[&n]      = reg_assigned;
  byte_code_.stream.push_back( IRBuilder::Load(reg_assigned, n.value) );
}


/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Visit(BinaryOp const& n){
  n.lhs->Accept(*this);
  n.rhs->Accept(*this);
  
  const uint32_t reg_assigned = reg_allocator_.freeRegister();
  reg_of_expression_[&n]      = reg_assigned;
  const uint32_t reg_src1     = reg_of_expression_[n.lhs];
  const uint32_t reg_src2     = reg_of_expression_[n.rhs];
  byte_code_.stream.push_back( IRBuilder::Add(reg_src1, reg_src2, 
                                              reg_assigned));
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::Print() const{
  VMUtils::print(byte_code_);
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorCodeGenerator::EndOfProgram(){
  byte_code_.stream.push_back( IRBuilder::Stop());
}