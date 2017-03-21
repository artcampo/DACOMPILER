#include "IR/IRStream.hpp"
#include "IR/IR.hpp"
#include "IR/IRSubtypes.hpp"

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
  Append( LoadI(val) );
  return RegAssignedToPreviousInst();
}

Reg IRStream::AppendLoad(const MemAddr addr){
  Append( Load(addr) );
  return RegAssignedToPreviousInst();
}

Reg IRStream::AppendLoadReg(const Reg src){
  Append( LoadReg(src) );
  return RegAssignedToPreviousInst();
}

Reg IRStream::AppendLoadRegOffs(const Reg src, const Offset o){
  Append( LoadRegOffs(src, o) );
  return RegAssignedToPreviousInst();
}

void IRStream::AppendStore(const Reg src, const MemAddr addr){
  Append( Store(src, addr) );
}

void IRStream::AppendStoreReg(const Reg src1, const Reg src2){
  Append( StoreReg(src1, src2) );
}


Reg IRStream::AppendArith(const Reg src1, const Reg src2, const ArithType op){
  Append( Arith(src1, src2, op) );
  return RegAssignedToPreviousInst();
}

Reg IRStream::AppendPtrElem(const MemAddr addr){
  Append( PtrElem(addr) );
  return RegAssignedToPreviousInst();
}

Reg IRStream::AppendGetRetVal(){
  Append( GetRetVal() );
  return RegAssignedToPreviousInst();
}
void IRStream::AppendSetRetVal(const Reg src){
  Append( SetRetVal(src) );
}

void IRStream::AppendSetPar(const Reg src)    { Append( SetPar(src) );}
void IRStream::AppendReturn()                 { Append( Return() ); }
void IRStream::AppendReturnMain()             { Append( ReturnMain() );  }
void IRStream::AppendCall(const MemAddr addr) { Append( Call(addr) );  };

Reg IRStream::RegAssignedToPreviousInst() const{
  Inst::InstDst& i = dynamic_cast<Inst::InstDst&>(*(stream_[ stream_.size() - 1 ]));
  return i.RegDst();
}

void IRStream::Print() const noexcept{
 Addr a = 0;
 std::cout << entry_label_.str() << "\n";
 for(auto& it : stream_){ std::cout << a << ": "<< it->str() << "\n"; ++a;}
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
