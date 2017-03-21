#pragma once
#include "Types.hpp"
#include "Types/BasicType.hpp"
#include "Types/PtrType.hpp"
#include "Types/FuncType.hpp"
#include "Types/ClassType.hpp"
#include "ErrorLog.hpp"
#include <memory>
#include <map>
#include <cstddef>


namespace Compiler{

using AST::TypeId;
using AST::kBasicTypeId;
using AST::Type;
using AST::BasicType;
using AST::PtrType;
using AST::FuncType;
using AST::ClassType;
// using AST::StructType;

/*
 * const Type& GetType(const kBasicTypeId basic_id)
 * const Type& PtrToT(const Type& t)
 * const Type& PointedBy(const Type& t)
 */


class TypeTable{
public:
  TypeTable(ErrorLog& error_log) : free_type_id_(0), error_log_(error_log){}


  const Type& GetTypeVoid(){ return GetType(kBasicTypeId::kVoid);}
  const Type& GetTypeInt() { return GetType(kBasicTypeId::kInt);}
  const Type& GetTypeBool(){ return GetType(kBasicTypeId::kBool);}

  const Type& GetTypePtrToInt(){return PtrToT(GetTypeInt());}
  const Type& GetTypePtrToBool(){return PtrToT(GetTypeInt());}

  const Type& PtrToT(const Type& t);
  const Type& PointedBy(const Type& t);

  const Type& GetFuncType(const Type& return_type
                        , const std::vector<const Type*>& arg_types);

  const ClassType& GetClassType(const std::string& name);

  const Type& GetType(const TypeId id) const{ return *type_table_.at(id);}

  const Type& GetTypeError(){ return GetType(kBasicTypeId::kError);}
  const Type& GetTypeUnknown(){ return GetType(kBasicTypeId::kUnknown);}

  void  SetClassTypeSize(const std::string& name, const size_t size){
    type_table_.at(type_id_of_class_.at(name))->SetSize(size);
  }
private:
  const Type& GetType(const kBasicTypeId basic_id);


private:
  ErrorLog&         error_log_;
  std::map<TypeId, std::unique_ptr<Type>> type_table_;
  std::map<kBasicTypeId, TypeId> type_id_of_basic_type_;
  std::map<TypeId, TypeId> type_id_of_pointer_to_t_;
  std::map<TypeId, TypeId> type_id_of_pointed_by_t_;
  std::map<std::vector<const Type*>, TypeId> type_id_of_function_by_signature_;
  std::map<std::string, TypeId> type_id_of_class_;
  size_t free_type_id_;

  const TypeId GetTypeId(const kBasicTypeId basic){
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
