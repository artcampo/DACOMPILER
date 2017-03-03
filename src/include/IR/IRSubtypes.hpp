#pragma once
#include <cstddef>

namespace Compiler{
namespace IR{

using AddrOffset  = int;
using Addr  = size_t;
using Reg   = size_t;

enum class ArithType{
    kAdd = 0
  , kSub = 1
  , kMul = 2
  , kDiv = 3
};

enum class CompType{
    kNotEqual = 0
  , kEqual = 1
  , kLessThan = 2
  , kLessEqualThan = 3
};


std::string str(const ArithType op)     noexcept;
std::string str(const CompType op)      noexcept;


}//end namespace IR
}//end namespace Compiler
