#pragma once
#include "IR/IR.hpp"
#include "IR/IRBuilder.hpp"
#include "Node.hpp"
#include <vector>

namespace Compiler{
namespace IR{

struct IRStream : public IRBuilder{
  Addr NextAddress() const noexcept{ return stream_.size(); }

  Inst& GetInst(const Addr addr) const noexcept{ return *stream_[addr];}

  void AppendJumpIfTrue(const Reg cond);
  void AppendJumpIfFalse(const Reg cond);
  void AppendJumpIfFalse(const Reg cond, const Addr target);
  void AppendJumpInconditional();

  Reg AppendLoadI(const NodeValue val);
  Reg AppendArith(const Reg src1, const Reg src2, const OpType op);
  void Print() const noexcept;
private:
  std::vector<PtrInst> stream_;

  void Append(PtrInst inst){ stream_.push_back( std::move(inst)); }

  Reg RegAssignedToPreviousInst() const;

};


}//end namespace IR
}//end namespace Compiler
