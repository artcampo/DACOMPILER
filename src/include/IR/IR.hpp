#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/IRSubtypes.hpp"
#include "IR/Label.hpp"
#include "IR/Offset.hpp"
#include "Node.hpp"

namespace Compiler{
namespace IR{

struct Inst;
struct JumpCond;
struct JumpIncond;
struct InstExpr;    //expression with a dest register
struct LoadI;
struct Load;
struct Store;
struct Arith;
struct Comparison;
struct AddrUnaryOp;

using PtrInst         = std::unique_ptr<Inst>;
using PtrJumpIncond   = std::unique_ptr<JumpIncond>;
using PtrJumpCond     = std::unique_ptr<JumpCond>;
using PtrLoadI        = std::unique_ptr<LoadI>;
using PtrLoad         = std::unique_ptr<Load>;
using PtrStore        = std::unique_ptr<Store>;
using PtrArith        = std::unique_ptr<Arith>;
using PtrComparison   = std::unique_ptr<Comparison>;
using PtrAddrUnaryOp  = std::unique_ptr<AddrUnaryOp>;



struct Inst{
  Inst(){};
  virtual ~Inst() = default;

  virtual std::string str() const noexcept = 0;
};


struct Jump: public  Inst{
  Jump() : target_(0){};
  Jump(const Addr target) : target_(target){};
  ~Jump() = default;

  void PatchJump(const Addr target){ target_ = target;}

  virtual std::string str() const noexcept{
    return std::string("Jump to ") + std::to_string(target_);
  };
protected:
  Addr target_;
};

struct JumpCond : public Jump{
  JumpCond(const Reg cond) : JumpCond(cond, 0){};
  JumpCond(const Reg cond, const Addr target) : Jump(target), cond_(cond){};
  ~JumpCond() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpCond ");
  };
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
  };
};

struct JumpCondTrue : public JumpCond{
  JumpCondTrue(const Reg cond) : JumpCond(cond){};
  JumpCondTrue(const Reg cond, const Addr target) : JumpCond(cond, target){};
  ~JumpCondTrue() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpCondTrue %") + std::to_string(cond_)
         + std::string(" to:")  + std::to_string(target_);
  };
};

struct JumpIncond : public Jump{
  JumpIncond() : Jump(){};
  ~JumpIncond() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpIncond") + std::to_string(target_);
  };
};

struct InstExpr : public Inst{
  InstExpr(const Reg reg_dst) : reg_dst_(reg_dst){};
  virtual ~InstExpr() = default;

  virtual std::string str() const noexcept = 0;
  Reg RegDst() const noexcept { return reg_dst_;};
protected:
  Reg reg_dst_;
};

struct LoadI : public InstExpr{
  LoadI(const Reg reg_dst, const NodeValue val) : InstExpr(reg_dst), val_(val){};
  virtual ~LoadI() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(reg_dst_)
         + std::string(" = LoadI(") + std::to_string(val_)
         + std::string(")") ;
  };
protected:
  NodeValue val_;
};

struct Load : public InstExpr{
  Load(const Reg reg_dst, const Label& l, const Offset o)
    : InstExpr(reg_dst), label_( std::move(l.Clone())), offset_(o){};
  virtual ~Load() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(reg_dst_)
         + std::string(" = Load [") + label_->str() + std::string(":") + offset_.str()
         + std::string("]");
  };
protected:
  PtrLabel label_;
  Offset offset_;
};


struct Store : public Inst{
  Store(const Reg src, const Label& l, const Offset o)
    : src_(src), label_( std::move(l.Clone())), offset_(o){};
  virtual ~Store() = default;

  virtual std::string str() const noexcept{
    return std::string("store %")  + std::to_string(src_)
         + std::string(" to [") + label_->str() + std::string(":") + offset_.str()
         + std::string("]") ;
  };
protected:
  Reg src_;
  PtrLabel label_;
  Offset offset_;
};


struct BinaryOp : public InstExpr{
  BinaryOp(const Reg reg_dst, const Reg src1, const Reg src2)
  : InstExpr(reg_dst), reg_src1_(src1), reg_src2_(src2){};
  virtual ~BinaryOp() = default;

  virtual std::string str() const noexcept = 0;

protected:
  Reg reg_src1_;
  Reg reg_src2_;
};

struct UnaryOp : public InstExpr{
  UnaryOp(const Reg reg_dst, const Reg src1)
  : InstExpr(reg_dst), reg_src1_(src1){};
  virtual ~UnaryOp() = default;

  virtual std::string str() const noexcept = 0;

protected:
  Reg reg_src1_;
};

struct Arith : public BinaryOp{
  Arith(const Reg reg_dst, const Reg src1, const Reg src2, const ArithType op)
  : BinaryOp(reg_dst, src1, src2), op_(op){};
  virtual ~Arith() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(reg_dst_)
         + std::string(" = %") + std::to_string(reg_src1_) + std::string(" ")
         + Compiler::IR::str(op_) + std::string(" %")+ std::to_string(reg_src2_);
  };
protected:
  ArithType op_;
};

struct Comparison : public BinaryOp{
  Comparison(const Reg reg_dst, const Reg src1, const Reg src2, const CompType op)
  : BinaryOp(reg_dst, src1, src2), op_(op){};
  virtual ~Comparison() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(reg_dst_)
         + std::string(" = %") + std::to_string(reg_src1_) + std::string(" ")
         + Compiler::IR::str(op_) + std::string(" %")+ std::to_string(reg_src2_);
  };
protected:
  CompType op_;
};

struct AddrUnaryOp : public UnaryOp{
  AddrUnaryOp(const Reg reg_dst, const Reg src1, const AddrUnaryType op)
  : UnaryOp(reg_dst, src1), op_(op){};
  virtual ~AddrUnaryOp() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(reg_dst_)
         + std::string(" = ") + Compiler::IR::str(op_)
         + std::string(" %") + std::to_string(reg_src1_);
  };
protected:
  AddrUnaryType op_;
};




}//end namespace IR
}//end namespace Compiler
