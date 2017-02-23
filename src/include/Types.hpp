#pragma once
#include "TypeId.hpp"
#include <cstddef>

/*
 * type_id must be unique
 */

namespace Compiler{
namespace AST{


enum class kBasicTypeId : size_t{
    kVoid
  , kInt  = 1
  , kBool = 2
};

class Type;

class Type{
public:
  virtual ~Type(){}
  Type(const TypeId& type_id) : type_id_(type_id){}
  virtual size_t      Size() const noexcept = 0;
  virtual std::string str() const noexcept = 0;
  virtual bool IsBool() const noexcept = 0;
  virtual bool IsPtr() const noexcept = 0;

  const bool operator<  ( const Type &type )const noexcept
    {return type_id_ < type.type_id_;}
  const bool operator==( const Type& t ) const noexcept
    {return type_id_ == t.type_id_;}
  const bool operator!=( const Type& t ) const noexcept
    {return not(type_id_ == t.type_id_);}

  TypeId GetTypeId() const noexcept {return type_id_;}

private:
  TypeId type_id_;
};

class BasicType : public Type{
public:
  virtual ~BasicType(){}
  BasicType(const TypeId& type_id, const kBasicTypeId& basic_id)
    : Type(type_id), basic_id_(basic_id){}

  virtual size_t  Size() const noexcept{ return 1;};
  virtual std::string str() const noexcept{
    if(basic_id_ == kBasicTypeId::kInt) return std::string("int");
    if(basic_id_ == kBasicTypeId::kBool) return std::string("bool");
    return std::string("BasicType not implemented.");
  }

  virtual bool IsBool() const noexcept{ return basic_id_ == kBasicTypeId::kBool;}
  virtual bool IsPtr() const noexcept{ return false;}

private:
  kBasicTypeId basic_id_;
};

class PtrType : public Type{
public:
  virtual ~PtrType(){}

  PtrType(const TypeId& type_id, const Type& pointed_type)
    : Type(type_id), pointed_tid_(pointed_type.GetTypeId())
    , pointed_str_(pointed_type.str()){}

  virtual size_t  Size() const noexcept{ return 1;};
  virtual std::string str() const noexcept{
    return pointed_str_ + std::string("*");
  }

  virtual bool IsBool() const noexcept{ return false;}
  virtual bool IsPtr() const noexcept{ return true;}

private:
  TypeId  pointed_tid_;
  const std::string pointed_str_;

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
