#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/IRSubtypes.hpp"


namespace Compiler{
namespace IR{


struct Offset{
  Offset(const Addr addr) : addr_(addr){}


  virtual std::string str() const noexcept{
  }
private:
  Addr addr_;
};


}//end namespace IR
}//end namespace Compiler
