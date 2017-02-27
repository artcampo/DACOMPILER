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
struct Jump;

using PtrInst = std::unique_ptr<Inst>;

struct Inst{
  Inst(){};
  virtual ~Inst() = default;

  virtual std::string str() const noexcept = 0;
};



struct Jump: Inst{
  Jump() : target_(0){};
  Jump(const Addr target) : target_(target){};
  virtual ~Jump() = default;
  virtual std::string str() = 0;

  void PatchJump(const Addr target){ target_ = target;}
private:
  Addr target_;
};

struct JumpCond : Jump{
  JumpCond(){};
  JumpCond(const Addr target) : Jump(target){};
  virtual ~JumpCond() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpCond ");
  };
};

struct JumpIncond: Jump{
  JumpIncond(){};
  virtual ~JumpIncond() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpIncond");
  };
};

}//end namespace IR
}//end namespace Compiler
