#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/IR.hpp"
#include "Node.hpp"

namespace Compiler{
namespace IR{

class IRBuilder{
protected:
  IRBuilder() : next_free_reg_(0){};

  PtrJumpCond JumpIfTrue(const Reg cond){
    return std::make_unique<JumpCondTrue>(cond);
  };

  PtrJumpCond JumpIfFalse(const Reg cond){
    return std::make_unique<JumpCondFalse>(cond);
  };

  PtrJumpCond JumpIfFalse(const Reg cond, const Addr target){
    return std::make_unique<JumpCondFalse>(cond, target);
  };

  PtrJumpIncond JumpInconditional(){
    return std::make_unique<JumpIncond>();
  };

  PtrLoadI LoadInmediate(const NodeValue val){
    Reg assigned_reg = next_free_reg_;
    next_free_reg_++;
    return std::make_unique<LoadI>(assigned_reg, val);
  }

private:
  Reg   next_free_reg_;
};

}//end namespace IR
}//end namespace Compiler
