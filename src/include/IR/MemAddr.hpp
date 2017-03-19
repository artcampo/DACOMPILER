#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/Label.hpp"
#include "IR/Offset.hpp"

namespace Compiler{
namespace IR{


struct MemAddr{
  MemAddr() = default;
  MemAddr(const Label l, const Offset o)
    : l_(l), o_(o){}

//   std::string str() const noexcept {return l_.str() + o_.str;}
  std::string str() const noexcept {return l_.str() + ":"+ o_.str();}

//   const bool operator<  ( const Offset &o )const noexcept
//     {return addr_ < o.addr_;}
private:
  Label   l_;
  Offset  o_;
};


}//end namespace IR
}//end namespace Compiler
