#pragma once
#include <cstddef>


namespace Compiler{
namespace AST{


enum class kFirstClass{ 
    typeid_int  = 0
  , typeid_bool = 1
};

  
class TypeId {
public:
  TypeId(){};
  TypeId(const kFirstClass id): id_(size_t(id)){}
  
  size_t Id() const noexcept {return id_;};
  
  static TypeId Int() noexcept{ return TypeId(kFirstClass::typeid_int);}
  static TypeId Bool() noexcept{ return TypeId(kFirstClass::typeid_bool);}
private:
  size_t id_;
};


}//end namespace AST
}//end namespace Compiler