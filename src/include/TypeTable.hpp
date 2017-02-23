#pragma once
#include "TypeId.hpp"
#include "Types.hpp"
#include <memory>
#include <map>
#include <cstddef>

namespace Compiler{

using AST::TypeId;
using AST::kBasicTypeId;
using AST::Type;
using AST::BasicType;



class TypeTable{
public:
  TypeTable() : free_type_id_(0){}

  const Type& GetType(const kBasicTypeId basic_id){
    const TypeId& type_id = GetTypeId(basic_id);
    auto it = type_table_.find(type_id);
    if(it == type_table_.end()){
      type_table_[type_id] = std::make_unique<BasicType>(basic_id, type_id);
      //type_table_[type_id] = std::unique_ptr<Type>( new BasicType(basic_id, type_id));
    }
    return *type_table_[type_id];
  }

private:
  std::map<TypeId, std::unique_ptr<Type>> type_table_;
  std::map<kBasicTypeId, TypeId> type_id_of_basic_type_;
  size_t free_type_id_;

  const TypeId& GetTypeId(const kBasicTypeId basic){
    auto it = type_id_of_basic_type_.find(basic);
    if(it == type_id_of_basic_type_.end())
      type_id_of_basic_type_[basic] = FreeTypeId();
    return type_id_of_basic_type_[basic];
  }

  const TypeId FreeTypeId(){
    TypeId t = TypeId(free_type_id_);
    free_type_id_++;
    return t;
  }
};

}//end namespace Compiler
