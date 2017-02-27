#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "Node.hpp"

namespace Compiler{
namespace IR{

using Addr  = size_t;
using Reg   = size_t;

struct Inst;
struct JumpCond;
struct JumpIncond;
struct InstExpr;    //expression with a dest register
struct LoadI;

using PtrInst       = std::unique_ptr<Inst>;
using PtrJumpIncond = std::unique_ptr<JumpIncond>;
using PtrJumpCond   = std::unique_ptr<JumpCond>;
using PtrLoadI      = std::unique_ptr<LoadI>;


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
    return std::string("JumpCondFalse reg:") + std::to_string(cond_)
         + std::string(" to:")  + std::to_string(target_);
  };
};

struct JumpCondTrue : public JumpCond{
  JumpCondTrue(const Reg cond) : JumpCond(cond){};
  JumpCondTrue(const Reg cond, const Addr target) : JumpCond(cond, target){};
  ~JumpCondTrue() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpCondTrue reg:") + std::to_string(cond_)
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
    return std::string("LoadI of") + std::to_string(val_)
         + std::string(" to:")  + std::to_string(reg_dst_);
  };
protected:
  NodeValue val_;
};

}//end namespace IR
}//end namespace Compiler
