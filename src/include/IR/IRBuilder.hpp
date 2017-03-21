#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/IR.hpp"
#include "AST/Node.hpp"

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

  Inst::PtrArith Arith(const Reg src1, const Reg src2, const ArithType op){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::Arith>(assigned_reg, src1, src2, op);
  }

  Inst::PtrLoadI LoadI(const NodeValue val){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::LoadI>(assigned_reg, val);
  }

  Inst::PtrLoad Load(const MemAddr addr){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::Load>(assigned_reg, addr);
  }

  Inst::PtrLoadReg LoadReg(const Reg src){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::LoadReg>(assigned_reg, src);
  }

  Inst::PtrLoadRegOffs LoadRegOffs(const Reg src, const Offset o){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::LoadRegOffs>(assigned_reg, src, o);
  }

  Inst::PtrStore Store(const Reg src, const MemAddr addr){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::Store>(src, addr);
  }

  //src1 is value to be stored, src2 contains address
  Inst::PtrStoreReg StoreReg(const Reg src1, const Reg src2){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::StoreReg>(src1, src2);
  }

  Inst::PtrPtrElem PtrElem(const MemAddr addr){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::PtrElem>(assigned_reg, addr);
  }

  Inst::PtrGetRetVal GetRetVal(){
    Reg assigned_reg = FreeReg();
    return std::make_unique<Inst::GetRetVal>(assigned_reg);
  }

  Inst::PtrSetRetVal SetRetVal(const Reg src){
    return std::make_unique<Inst::SetRetVal>(src);
  }

  Inst::PtrSetPar SetPar(const Reg src){
    return std::make_unique<Inst::SetPar>(src);
  }

  Inst::PtrReturn Return(){
    return std::make_unique<Inst::Return>();
  }

  Inst::PtrReturnMain ReturnMain(){
    return std::make_unique<Inst::ReturnMain>();
  }

  Inst::PtrCall Call(const MemAddr addr){
    return std::make_unique<Inst::Call>(addr);
  }


private:
  Reg   next_free_reg_;

  Reg   FreeReg(){return next_free_reg_++;}
};

}//end namespace IR
}//end namespace Compiler
