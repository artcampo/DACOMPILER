#pragma once
#include "Types.hpp"

namespace Compiler{
namespace AST{

//Provides range-for iteration over its par types
class FuncType : public Type{
public:
  virtual ~FuncType() = default;

  FuncType(const TypeId& type_id, const Type& return_type
    , const std::vector<const Type*>& par_types)
    : Type(type_id, 1), return_tid_(return_type.GetTypeId())
    , ret_str_(return_type.str())
    {
      pars_str_ = std::string("");
      bool first_par = true;
      for(auto& it : par_types){
        if(not first_par) pars_str_ += ", ";
        pars_str_ += it->str();
        first_par = false;
      }
      for(auto& it : par_types) pars_tid_.push_back( it->GetTypeId());
    }

  virtual std::string str() const noexcept{
    return std::string("function: (") + pars_str_ + std::string(")->") + ret_str_;
  }

  virtual bool IsBool()  const noexcept{ return false;}
  virtual bool IsPtr()   const noexcept{ return false;}
  virtual bool IsFunc()  const noexcept{ return true;}
  virtual bool IsClass() const noexcept{ return false;}

  size_t  NumPars() const noexcept{ return pars_tid_.size();};

  const TypeId  RetTypeId() const noexcept{ return return_tid_;};

private:
  TypeId              return_tid_;
  std::vector<TypeId> pars_tid_;
  const std::string   ret_str_;
  std::string         pars_str_;

public:
  using iterator = std::vector<TypeId>::iterator;
  using const_iterator = std::vector<TypeId>::const_iterator;

  iterator begin() { return pars_tid_.begin(); }
  iterator end()   { return pars_tid_.end(); }
  const_iterator begin()  const { return pars_tid_.begin(); }
  const_iterator end()    const { return pars_tid_.end(); }
  const_iterator cbegin() const { return pars_tid_.cbegin(); }
  const_iterator cend()   const { return pars_tid_.cend(); }
};

}//end namespace AST
}//end namespace Compiler
