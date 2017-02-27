#pragma once
#include "IR/IR.hpp"

namespace Compiler{
namespace IR{

struct IRStream{
  Addr NextAddress() const noexcept{ return stream_.size(); }

  Inst& GetInst(const Addr addr) const noexcept{ return *stream_[addr];}
private:
  std::vector<PtrInst> stream_;
};


}//end namespace IR
}//end namespace Compiler
