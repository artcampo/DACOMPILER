#pragma once
#include "Types/TypeId.hpp"
#include <cstddef>
#include <vector>
#include <string>

/*
 * type_id must be unique
 */

namespace Compiler{
namespace AST{


enum class kBasicTypeId : size_t{
    kVoid = 0
  , kInt  = 1
  , kBool = 2
  //used when an expression's type could not be determined
  , kError = 3
  //used when a type is unknow at parsing but will be later resolved
  , kUnknown = 4
};

class Type;
class BasicType;
class PtrType;
class FuncType;
class ClassType;

class Type{
public:
  virtual ~Type(){}
  Type(const TypeId& type_id, const size_t size)
    : type_id_(type_id), size_(size){}

  virtual std::string str() const noexcept = 0;
  virtual bool IsBool()     const noexcept = 0;
  virtual bool IsPtr()      const noexcept = 0;
  virtual bool IsFunc()     const noexcept = 0;
  virtual bool IsClass()    const noexcept = 0;

  const bool operator<  ( const Type &type )const noexcept
    {return type_id_ < type.type_id_;}
  const bool operator==( const Type& t ) const noexcept
    {return type_id_ == t.type_id_;}
  const bool operator!=( const Type& t ) const noexcept
    {return not(type_id_ == t.type_id_);}

  TypeId  GetTypeId() const noexcept {return type_id_;}
  size_t  Size() const noexcept{ return size_;}
  void    SetSize(const size_t size) noexcept { size_ = size ;}

private:
  TypeId type_id_;
  size_t size_;
};


/*


class StructType : public Type{
public:
  virtual ~PtrcType(){}


  virtual size_t  Size() const noexcept{ return 1;};
  virtual std::string str() const noexcept{
    return std::string("BasicType not implemented.");
  }

  virtual bool IsBool() const noexcept{ return false;}
  virtual bool IsPtr() const noexcept{ return false;}

private:

};

 */


}//end namespace AST
}//end namespace Compiler
