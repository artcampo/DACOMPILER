#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/IRSubtypes.hpp"

namespace Compiler{
namespace IR{

// name is a parameter used for debug. NOT for indexing
struct Offset{
  Offset() = default;
  Offset(const Offset &o) = default;
  Offset& operator= ( const Offset &o ) = default;

  Offset(const AddrOffset addr, const std::string& name)
    : addr_(addr), name_(name){}
  Offset(const AddrOffset addr)
    : addr_(addr), name_(""){}

  std::string str() const noexcept{
    //return std::to_string(addr_) + std::string(" ") + name_;
    return name_ + " " + std::to_string(addr_);
  }

  const bool operator<  ( const Offset &o )const noexcept
    {return addr_ < o.addr_;}

private:
  AddrOffset  addr_;
  std::string name_;
};


}//end namespace IR
}//end namespace Compiler
