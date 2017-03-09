#pragma once
#include "Types.hpp"

namespace Compiler{
namespace AST{

class ClassType : public Type{
public:
  virtual ~ClassType() = default;

  ClassType(const TypeId& type_id, const std::string& name)
    : Type(type_id), name_(name){}

  virtual size_t  Size() const noexcept{ return 1;};
  virtual std::string str() const noexcept{
    return name_;
  }

  virtual bool IsBool()  const noexcept{ return false;}
  virtual bool IsPtr()   const noexcept{ return false;}
  virtual bool IsFunc()  const noexcept{ return false;}
  virtual bool IsClass() const noexcept{ return true;}

private:
  const std::string name_;

};

}//end namespace AST
}//end namespace Compiler
