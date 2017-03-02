#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/IRSubtypes.hpp"

namespace Compiler{
namespace IR{

// name is a parameter used for debug. NOT for indexing
struct Offset{
  Offset(){}
  Offset(const AddrOffset addr, const std::string name)
    : addr_(addr), name_(name){}

  Offset(const Offset &o){ addr_ = o.addr_; name_ = o.name_; }
  Offset& operator= ( const Offset &o ){ addr_ = o.addr_; name_ = o.name_; }

  virtual std::string str() const noexcept{
    //return std::to_string(addr_) + std::string(" ") + name_;
    return name_;
  }

  const bool operator<  ( const Offset &o )const noexcept
    {return addr_ < o.addr_;}
private:
  AddrOffset addr_;
  std::string name_;
};


}//end namespace IR
}//end namespace Compiler
