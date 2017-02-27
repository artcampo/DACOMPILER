#pragma once
#include <string>
#include <memory>
#include <cstddef>

namespace Compiler{
namespace IR{

using Addr  = size_t;
using Reg   = size_t;

struct Inst;
struct JumpCond;
struct JumpIncond;

using PtrInst       = std::unique_ptr<Inst>;
using PtrJumpIncond = std::unique_ptr<JumpIncond>;
using PtrJumpCond   = std::unique_ptr<JumpCond>;


struct Inst{
  Inst(){};
  virtual ~Inst() = default;

  virtual std::string str() const noexcept = 0;
};



struct Jump: Inst{
  Jump() : target_(0){};
  Jump(const Addr target) : target_(target){};
  ~Jump() = default;

  void PatchJump(const Addr target){ target_ = target;}

  virtual std::string str() const noexcept{
    return std::string("Jump to ") + std::to_string(target_);
  };
private:
  Addr target_;
};

struct JumpCond : Jump{
  JumpCond(const Reg cond) : JumpCond(cond, 0){};
  JumpCond(const Reg cond, const Addr target) : Jump(target), cond_(cond){};
  ~JumpCond() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpCond ");
  };
private:
  Reg cond_;
};

struct JumpIncond: Jump{
  JumpIncond(){};
  ~JumpIncond() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpIncond");
  };
};

}//end namespace IR
}//end namespace Compiler
