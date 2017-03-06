#pragma once
#include "IR/IR.hpp"
#include "IR/IRBuilder.hpp"
#include "Node.hpp"
#include <vector>

namespace Compiler{
namespace IR{


struct IRStream : public IRBuilder{
  Addr NextAddress() const noexcept{ return stream_.size(); }

  Inst::Inst& GetInst(const Addr addr) const noexcept{ return *stream_[addr];}

  void AppendJumpIfTrue(const Reg cond);
  void AppendJumpIfFalse(const Reg cond);
  void AppendJumpIfFalse(const Reg cond, const Addr target);
  void AppendJumpInconditional();

  void AppendStore(const Reg src,const MemAddr addr);
  void AppendStoreReg(const Reg src1, const Reg src2);

  Reg AppendLoadI(const NodeValue val);
  Reg AppendLoad(const MemAddr addr);
  Reg AppendLoadReg(const Reg src);
  Reg AppendArith(const Reg src1, const Reg src2, const ArithType op);
  Reg AppendPtrElem(const MemAddr addr);

  Reg AppendGetRetVal();
  void AppendSetRetVal(const Reg src);
  void AppendSetPar(const Reg src);
  void AppendReturn();
  void AppendReturnMain();
  void AppendCall(const MemAddr addr);


  void Print() const noexcept;
private:
  std::vector<Inst::PtrInst> stream_;

  void Append(Inst::PtrInst inst){ stream_.push_back( std::move(inst)); }

  Reg RegAssignedToPreviousInst() const;

};


}//end namespace IR
}//end namespace Compiler
