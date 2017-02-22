#pragma once
#include <cstddef>


namespace Compiler{
namespace AST{


enum class kFirstClass : size_t{
    typeid_int  = 0
  , typeid_bool = 1
};


class TypeId {
public:
  TypeId(){};
  TypeId(const kFirstClass id): id_(size_t(id)){}

  size_t Id() const noexcept {return id_;};

  static TypeId Int()  noexcept{ return TypeId(kFirstClass::typeid_int);}
  static TypeId Bool() noexcept{ return TypeId(kFirstClass::typeid_bool);}

  std::string str()const noexcept{
    if(id_ == size_t(kFirstClass::typeid_int)) return std::string("int");
    if(id_ == size_t(kFirstClass::typeid_bool)) return std::string("bool");
    return std::string("type_uknown");
  }

  const bool operator< ( const TypeId &t ) const{return id_ < t.id_;}
  TypeId& operator= ( const TypeId &t ){id_ = t.id_;}
  const bool operator== ( const TypeId &t ) const noexcept {return id_ == t.id_;}

  bool IsBool() const noexcept{ return id_ == size_t(kFirstClass::typeid_bool);}
  bool IsInt() const noexcept{ return id_ == size_t(kFirstClass::typeid_int);}
private:
  size_t id_;
};


}//end namespace AST
}//end namespace Compiler
