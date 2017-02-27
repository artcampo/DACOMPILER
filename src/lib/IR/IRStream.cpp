#include "IR/IRStream.hpp"

namespace Compiler{
namespace IR{


void IRStream::AppendJumpIfTrue(const Reg cond){
  Append( JumpIfTrue(cond) );
}

void IRStream::AppendJumpIfFalse(const Reg cond){

}

void IRStream::AppendJumpIncond(){

}

}//end namespace IR
}//end namespace Compiler
