#include "ASTVisitorCodeGenerator.hpp"
#include "IRBuilder.hpp"
#include "Utils.hpp"

namespace Compiler{
namespace AST{

/////////////////////////////////////////////////////////////////////////////
void CodeGen::Visit(Block const& n, const Statement* successor) {
  bool patch = false;
  for (auto c : n.statements){
      //std::cout << "patching " << back_patch_.top()->str() << "to: " <<
//       c->Accept(*this, back_patch);
//       patch = not back_patch_.empty();

  }
}

void CodeGen::Visit(AssignStmt const& p, const Statement* successor){

}
void CodeGen::Visit(DeclStmt const& p, const Statement* successor){

}
void CodeGen::Visit(IfStmt const& p, const Statement* successor){
//   back_patch_.push(&p);
}


/////////////////////////////////////////////////////////////////////////////
void CodeGen::Visit(Literal const& n, const Statement* successor){
  const uint32_t reg_assigned = reg_allocator_.freeRegister();
  reg_of_Expr_[&n]      = reg_assigned;
  byte_code_.stream.push_back( IRBuilder::Load(reg_assigned, n.Value()) );
}


/////////////////////////////////////////////////////////////////////////////
void CodeGen::Visit(BinaryOp const& n, const Statement* successor){
  n.Lhs()->Accept(*this, successor);
  n.Rhs()->Accept(*this, successor);

  const uint32_t reg_assigned = reg_allocator_.freeRegister();
  reg_of_Expr_[&n]      = reg_assigned;
  const uint32_t reg_src1     = reg_of_Expr_[n.Lhs()];
  const uint32_t reg_src2     = reg_of_Expr_[n.Rhs()];
  const uint32_t op           = n.op;
  byte_code_.stream.push_back( IRBuilder::Arith(reg_src1, reg_src2,
                                                reg_assigned, op));
//   std::cout << "OP: " << op << "\n";
}

/////////////////////////////////////////////////////////////////////////////
void CodeGen::Print() const{
  VMUtils::print(byte_code_);
}

/////////////////////////////////////////////////////////////////////////////
void CodeGen::EndOfProgram(){
  byte_code_.stream.push_back( IRBuilder::Stop());
  Print();
}

}//end namespace AST
}//end namespace Compiler
