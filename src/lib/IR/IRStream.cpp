#include "IR/IRStream.hpp"
#include "IR/IR.hpp"

namespace Compiler{
namespace IR{


void IRStream::AppendJumpIfTrue(const Reg cond){
  Append( JumpIfTrue(cond) );
}

void IRStream::AppendJumpIfFalse(const Reg cond){
  Append( JumpIfFalse(cond) );
}

void IRStream::AppendJumpIfFalse(const Reg cond, const Addr target){
  Append( JumpIfFalse(cond, target) );
}

void IRStream::AppendJumpInconditional(){
  Append( JumpInconditional() );
}

Reg IRStream::AppendLoadI(const NodeValue val){
  Append( LoadInmediate(val) );
  return RegAssignedToPreviousInst();
}

Reg IRStream::AppendArith(const Reg src1, const Reg src2, const OpType op){
  Append( Arithmetic(src1, src2, op) );
  return RegAssignedToPreviousInst();
}

Reg IRStream::RegAssignedToPreviousInst() const{
  InstExpr& i = dynamic_cast<InstExpr&>(*(stream_[ stream_.size() - 1 ]));
  return i.RegDst();
}



}//end namespace IR

std::string str(const OpType op) noexcept{
  if(op == 0) return std::string("+");
  if(op == 1) return std::string("-");
  if(op == 2) return std::string("*");
  if(op == 3) return std::string("/");
  return std::string("not implemented, code 42");
}

}//end namespace Compiler
