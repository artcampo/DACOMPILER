#pragma once
#include <string>

namespace Compiler{
namespace IR{

using Addr   = uint32_t;

struct Inst{
  Inst();
  virtual ~Inst() = default;

  virtual std::string str() const noexcept = 0;
};

struct JumpCond : Inst{
  JumpCond();
  virtual ~JumpCond() = default;

  virtual std::string str() const noexcept{
    return std::string("JumpCond ");
  };
};

struct Jump: Inst{
  Jump();
  virtual ~Jump() = default;

  virtual std::string str() const noexcept{
    return std::string("Jump ");
  };
};

}//end namespace IR
}//end namespace Compiler
