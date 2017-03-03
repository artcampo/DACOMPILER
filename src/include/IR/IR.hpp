#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/IRSubtypes.hpp"
#include "IR/Label.hpp"
#include "IR/Offset.hpp"
#include "IR/MemAddr.hpp"
#include "Node.hpp"

namespace Compiler{
namespace IR{
namespace Inst{

struct Inst;
struct JumpCond;
struct JumpIncond;
struct LoadI;
struct Load;
struct LoadReg;
struct Store;
struct StoreReg;
struct Arith;
struct Comparison;
struct PtrElem;

using PtrInst         = std::unique_ptr<Inst>;
using PtrJumpIncond   = std::unique_ptr<JumpIncond>;
using PtrJumpCond     = std::unique_ptr<JumpCond>;
using PtrLoadI        = std::unique_ptr<LoadI>;
using PtrLoad         = std::unique_ptr<Load>;
using PtrLoadReg      = std::unique_ptr<LoadReg>;
using PtrStore        = std::unique_ptr<Store>;
using PtrStoreReg     = std::unique_ptr<StoreReg>;
using PtrArith        = std::unique_ptr<Arith>;
using PtrComparison   = std::unique_ptr<Comparison>;
using PtrPtrElem      = std::unique_ptr<PtrElem>;


struct InstAddress{
  InstAddress(const MemAddr addr)
    :addr_(addr){}
  ~InstAddress() = default;
protected:
  MemAddr addr_;
};

struct InstSrc{
  InstSrc(const Reg src) : src_(src){}
  ~InstSrc() = default;
  Reg RegSrc() const noexcept { return src_;};
protected:
  Reg src_;
};

struct InstSrcSrc{
  InstSrcSrc(const Reg src1, const Reg src2) : src1_(src1), src2_(src2){}
  ~InstSrcSrc() = default;
  Reg RegSrc1() const noexcept { return src1_;};
  Reg RegSrc2() const noexcept { return src2_;};
protected:
  Reg src1_;
  Reg src2_;
};

struct InstDst {
  InstDst(const Reg reg_dst) : dst_(reg_dst){};
  ~InstDst() = default;

  Reg RegDst() const noexcept { return dst_;};
protected:
  Reg dst_;
};

struct InstVal {
  InstVal( const NodeValue val) : val_(val){};
  ~InstVal() = default;

  NodeValue Value() const noexcept { return val_;};
protected:
  NodeValue val_;
};


//Interface
struct Inst{
  Inst(){};
  virtual ~Inst() = default;

  virtual std::string str() const noexcept = 0;
};


struct Jump: public Inst{
  Jump() : target_(0){};
  Jump(const Addr target) : target_(target){};
  ~Jump() = default;

  void PatchJump(const Addr target){ target_ = target;}

  virtual std::string str() const noexcept{
    return std::string("Jump to ") + std::to_string(target_);
  }
protected:
  Addr target_;
};

struct JumpCond : public Jump{
  JumpCond(const Reg cond) : JumpCond(cond, 0){};
  JumpCond(const Reg cond, const Addr target) : Jump(target), cond_(cond){};
  ~JumpCond() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpCond ");
  }
protected:
  Reg cond_;
};

struct JumpCondFalse : public JumpCond{
  JumpCondFalse(const Reg cond) : JumpCond(cond){};
  JumpCondFalse(const Reg cond, const Addr target) : JumpCond(cond, target){};
  ~JumpCondFalse() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpCondFalse %") + std::to_string(cond_)
         + std::string(" to:")  + std::to_string(target_);
  }
};

struct JumpCondTrue : public JumpCond{
  JumpCondTrue(const Reg cond) : JumpCond(cond){};
  JumpCondTrue(const Reg cond, const Addr target) : JumpCond(cond, target){};
  ~JumpCondTrue() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpCondTrue %") + std::to_string(cond_)
         + std::string(" to:")  + std::to_string(target_);
  }
};

struct JumpIncond : public Jump{
  JumpIncond() : Jump(){};
  ~JumpIncond() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpIncond") + std::to_string(target_);
  }
};


struct LoadI : public Inst, public InstDst, public InstVal{
  LoadI(const Reg reg_dst, const NodeValue val)
    : InstDst(reg_dst), InstVal(val){};
  virtual ~LoadI() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = LoadI(") + std::to_string(val_)
         + std::string(")") ;
  }
};

struct Load : public Inst, public InstDst, public InstAddress{
  Load(const Reg reg_dst, const MemAddr addr)
    : InstDst(reg_dst), InstAddress(addr){};
  virtual ~Load() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = Load [") + addr_.str()
         + std::string("]");
  }
};


struct LoadReg : public Inst, public InstDst, public InstSrc{
  LoadReg(const Reg reg_dst, const Reg reg_src)
    : InstDst(reg_dst), InstSrc(reg_src){};
  virtual ~LoadReg() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = Load [ %") + std::to_string(src_)
         + std::string("]");
  }
};



struct Store : public Inst, public InstSrc, public InstAddress{
  Store(const Reg src, const MemAddr addr)
    : InstSrc(src), InstAddress(addr){};
  virtual ~Store() = default;

  virtual std::string str() const noexcept{
    return std::string("store %")  + std::to_string(src_)
         + std::string(" to [") + addr_.str()
         + std::string("]") ;
  }
};

struct StoreReg : public Inst, public InstSrcSrc{
  StoreReg(const Reg src1, const Reg src2)
    : InstSrcSrc(src1, src2){};
  virtual ~StoreReg() = default;

  virtual std::string str() const noexcept{
    return std::string("store %")  + std::to_string(src1_)
         + std::string(" to [%") + std::to_string(src2_)
         + std::string("]") ;
  }
};



struct BinaryOp : public Inst, public InstDst, public InstSrcSrc{
  BinaryOp(const Reg reg_dst, const Reg src1, const Reg src2)
  : InstDst(reg_dst), InstSrcSrc(src1, src2){};
  virtual ~BinaryOp() = default;

  virtual std::string str() const noexcept = 0;
};

struct UnaryOp : public Inst, public InstDst, public InstSrc{
  UnaryOp(const Reg reg_dst, const Reg src1)
  : InstDst(reg_dst), InstSrc(src1){};
  virtual ~UnaryOp() = default;

  virtual std::string str() const noexcept = 0;
};

struct Arith : public BinaryOp{
  Arith(const Reg reg_dst, const Reg src1, const Reg src2, const ArithType op)
  : BinaryOp(reg_dst, src1, src2), op_(op){};
  virtual ~Arith() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = %") + std::to_string(src1_) + std::string(" ")
         + Compiler::IR::str(op_) + std::string(" %")+ std::to_string(src2_);
  }
protected:
  ArithType op_;
};

struct Comparison : public BinaryOp{
  Comparison(const Reg reg_dst, const Reg src1, const Reg src2, const CompType op)
  : BinaryOp(reg_dst, src1, src2), op_(op){};
  virtual ~Comparison() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = %") + std::to_string(src1_) + std::string(" ")
         + Compiler::IR::str(op_) + std::string(" %")+ std::to_string(src2_);
  }
protected:
  CompType op_;
};

struct PtrElem : public Inst, public InstAddress, public InstDst{
  PtrElem(const Reg reg_dst, const MemAddr addr)
    : InstAddress(addr), InstDst(reg_dst){}
  virtual ~PtrElem() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = PtrElem( ")
         + addr_.str() + std::string(")");
  }
};


}//end namespace Inst
}//end namespace IR
}//end namespace Compiler
