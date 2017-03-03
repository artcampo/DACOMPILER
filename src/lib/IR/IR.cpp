#include "IR/IR.hpp"

namespace Compiler{
namespace IR{

std::string str(const ArithType op) noexcept{
  if(ArithType::kAdd == op) return std::string("+");
  if(ArithType::kSub == op) return std::string("-");
  if(ArithType::kMul == op) return std::string("*");
  if(ArithType::kDiv == op) return std::string("/");
}

std::string str(const CompType op) noexcept{
  if(CompType::kNotEqual == op)      return std::string("!=");
  if(CompType::kEqual == op)         return std::string("==");
  if(CompType::kLessThan == op)      return std::string("<");
  if(CompType::kLessEqualThan == op) return std::string("<=");
}

}//end namespace IR
}//end namespace Compiler
