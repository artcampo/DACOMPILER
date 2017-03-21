#pragma once
#include "Types.hpp"

namespace Compiler{
namespace AST{

class PtrType : public Type{
public:
  virtual ~PtrType() = default;

  PtrType(const TypeId& type_id, const Type& pointed_type)
    : Type(type_id, 1), pointed_tid_(pointed_type.GetTypeId())
    , pointed_str_(pointed_type.str()){}

  virtual std::string str() const noexcept{
    return pointed_str_ + std::string("*");
  }

  virtual bool IsBool()  const noexcept{ return false;}
  virtual bool IsPtr()   const noexcept{ return true;}
  virtual bool IsFunc()  const noexcept{ return false;}
  virtual bool IsClass() const noexcept{ return false;}

private:
  TypeId  pointed_tid_;
  const std::string pointed_str_;

};

}//end namespace AST
}//end namespace Compiler
