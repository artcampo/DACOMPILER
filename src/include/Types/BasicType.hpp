#pragma once
#include "Types.hpp"

namespace Compiler{
namespace AST{

class BasicType : public Type{
public:
  virtual ~BasicType() = default;
  BasicType(const TypeId& type_id, const kBasicTypeId& basic_id)
    : Type(type_id, 1), basic_id_(basic_id){}

  virtual std::string str() const noexcept{
    if(basic_id_ == kBasicTypeId::kInt) return std::string("int");
    if(basic_id_ == kBasicTypeId::kBool) return std::string("bool");
    if(basic_id_ == kBasicTypeId::kVoid) return std::string("void");
    if(basic_id_ == kBasicTypeId::kError) return std::string("typeError");
    if(basic_id_ == kBasicTypeId::kUnknown) return std::string("typeUnknown");
    return std::string("BasicType not implemented.");
  }

  virtual bool IsBool()  const noexcept{ return basic_id_ == kBasicTypeId::kBool;}
  virtual bool IsPtr()   const noexcept{ return false;}
  virtual bool IsFunc()  const noexcept{ return false;}
  virtual bool IsClass() const noexcept{ return false;}

private:
  kBasicTypeId basic_id_;
};


}//end namespace AST
}//end namespace Compiler
