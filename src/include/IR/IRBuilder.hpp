#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/IR.hpp"

namespace Compiler{
namespace IR{

class IRBuilder{
protected:
  IRBuilder() : next_free_reg_(0){};

  PtrJumpCond JumpIfTrue(const Reg cond){
    return std::make_unique<JumpCond>(cond);
  };

private:
  Reg   next_free_reg_;
};

}//end namespace IR
}//end namespace Compiler
