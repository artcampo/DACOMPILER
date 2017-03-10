#pragma once
#include "Types.hpp"

/*
 * The type fingerprint for a class is only its name.
 * To make the whole interface uniform, ClassType only contains its
 * TypeId for checking (name is only used for printing).
 */

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
