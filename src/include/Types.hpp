#pragma once
#include <cstddef>


namespace Compiler{
namespace AST{


enum class kFirstClass : size_t{
    typeid_int  = 0
  , typeid_bool = 1
};

class Type;

class Type {
public:
  Type(){};
  static Type Int()  noexcept{ return Type(kFirstClass::typeid_int);}
  static Type Bool() noexcept{ return Type(kFirstClass::typeid_bool);}

  static Type PtrToInt()  noexcept{ return PtrToT(Int());}
  static Type PtrToBool() noexcept{ return PtrToT(Bool());}

  static Type PtrToT(const Type t){ return Type(t.id_, t);}

  size_t Id() const noexcept {return id_;};
  bool IsBool() const noexcept{ return id_ == size_t(kFirstClass::typeid_bool);}
  bool IsInt() const noexcept { return id_ == size_t(kFirstClass::typeid_int);}

  bool    IsPtr() const noexcept{ return is_pointer_;}
  Type  PointedType() const noexcept{ return *pointed_type_;}

  std::string str()const noexcept{
    if(id_ == size_t(kFirstClass::typeid_int)){
      if(not is_pointer_) return std::string("int");
      else                return std::string("int*");
    }
    if(id_ == size_t(kFirstClass::typeid_bool)){
      if(not is_pointer_) return std::string("bool");
      else                return std::string("bool*");
    }
    return std::string("type_uknown");
  }

  const bool operator<  ( const Type &t )const{
    if(id_ != t.id_)  return id_ < t.id_;
    else              return is_pointer_ < t.is_pointer_;
  }
  Type&    operator=  ( const Type &t )
  {id_ = t.id_; is_pointer_ = t.is_pointer_;}
  const bool operator== ( const Type &t ) const noexcept
  {return id_ == t.id_ and is_pointer_ == t.is_pointer_;}

  Type(const Type& t) : id_(t.id_), is_pointer_(t.is_pointer_){
      if(is_pointer_)
        //pointed_type_ = std::make_unique<Type>(*(t.pointed_type_.get()));
        pointed_type_ = std::unique_ptr<const Type>(new Type{*(t.pointed_type_.get())});
      else
        pointed_type_ = nullptr;
    }

private:
  size_t  id_;
  bool    is_pointer_;
  std::unique_ptr<const Type>  pointed_type_;
//   const Type*  pointed_type_;
  //TODO: if pointer should store Id of pointed T

  Type(const size_t id, const Type t)
  : id_(id),is_pointer_(true), pointed_type_(std::make_unique<Type>(t)){}
//   Type(const size_t id, const Type t)
//   : id_(size_t(id)),is_pointer_(true), pointed_type_(&t){}

  Type(const kFirstClass id)
  : id_(size_t(id)),is_pointer_(false)
  ,pointed_type_(nullptr){}

};


}//end namespace AST
}//end namespace Compiler
