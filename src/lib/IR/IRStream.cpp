#include "IR/IRStream.hpp"

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

Reg IRStream::RegAssignedToPreviousInst() const{
  InstExpr& i = dynamic_cast<InstExpr&>(*(stream_[ stream_.size() - 1 ]));
  return i.RegDst();
}

}//end namespace IR
}//end namespace Compiler
