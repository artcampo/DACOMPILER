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

  Inst::PtrJumpCond JumpIfTrue(const Reg cond){
    return std::make_unique<Inst::JumpCondTrue>(cond);
  };

  Inst::PtrJumpCond JumpIfFalse(const Reg cond){
    return std::make_unique<Inst::JumpCondFalse>(cond);
  };

  Inst::PtrJumpCond JumpIfFalse(const Reg cond, const Addr target){
    return std::make_unique<Inst::JumpCondFalse>(cond, target);
  };

  Inst::PtrJumpIncond JumpInconditional(){
    return std::make_unique<Inst::JumpIncond>();
  };

  Inst::PtrLoadI LoadInmediate(const NodeValue val){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::LoadI>(assigned_reg, val);
  }

  Inst::PtrArith Arithmetic(const Reg src1, const Reg src2, const ArithType op){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::Arith>(assigned_reg, src1, src2, op);
  }

  Inst::PtrLoad LoadMem(const Label& l, const Offset o){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::Load>(assigned_reg, l, o);
  }

  Inst::PtrStore StoreMem(const Reg src, const Label& l, const Offset o){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::Store>(src, l, o);
  }

  Inst::PtrAddrUnaryOp AddrUnary(const Reg src1, const AddrUnaryType op){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::AddrUnaryOp>(assigned_reg, src1, op);
  }



private:
  Reg   next_free_reg_;

  Reg   FreeReg(){
    next_free_reg_++;
    return next_free_reg_ - 1;
  }
};

}//end namespace IR
}//end namespace Compiler
