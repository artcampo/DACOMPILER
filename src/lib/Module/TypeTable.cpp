#include "Module/TypeTable.hpp"

namespace Compiler{

const Type& TypeTable::GetType(const kBasicTypeId basic_id){
  const TypeId type_id = GetTypeId(basic_id);
  auto it = type_table_.find(type_id);
  if(it == type_table_.end()){
    type_table_[type_id] = std::make_unique<BasicType>(type_id, basic_id);
    //type_table_[type_id] = std::unique_ptr<Type>( new BasicType(basic_id, type_id));
  }
  return *type_table_[type_id];
}

const Type& TypeTable::PtrToT(const Type& t){
  const TypeId t_id = t.GetTypeId();
  auto it = type_id_of_pointer_to_t_.find(t_id);
  if(it == type_id_of_pointer_to_t_.end()){
    const TypeId pointer_id = FreeTypeId();
    type_id_of_pointer_to_t_[t_id] = pointer_id;
    type_id_of_pointed_by_t_[pointer_id] = t_id;
    type_table_[pointer_id] = std::make_unique<PtrType>(pointer_id, t);
    return *type_table_[pointer_id];
  }
  return *type_table_[it->second];
}

const Type& TypeTable::PointedBy(const Type& t){
  const TypeId t_id = t.GetTypeId();
  auto it = type_id_of_pointed_by_t_.find(t_id);
  if(it == type_id_of_pointed_by_t_.end())
    error_log_.FatalError("pointed type not registered");
  return *type_table_[it->second];
}

const Type& TypeTable::GetFuncType(const Type& return_type
                        , const std::vector<const Type*>& arg_types){
  std::vector<const Type*> type_signature(arg_types);
  type_signature.push_back(const_cast<Type*>(&return_type));

  auto it = type_id_of_function_by_signature_.find(type_signature);
  if(it == type_id_of_function_by_signature_.end()){
    const TypeId func_id = FreeTypeId();
    type_id_of_function_by_signature_[type_signature] = func_id;

    type_table_[func_id] =
      std::make_unique<FuncType>(func_id, return_type, arg_types);
    return *type_table_[func_id];
  }
  return *type_table_[it->second];
}

const ClassType& TypeTable::GetClassType(const std::string& name){
  auto it = type_id_of_class_.find(name);
  if(it == type_id_of_class_.end()){
    const TypeId id = FreeTypeId();
    type_id_of_class_[name] = id;
    type_table_[id] = std::make_unique<ClassType>(id, name);
    return dynamic_cast<const ClassType&>(*type_table_[id]);
  }
  return dynamic_cast<const ClassType&>(*type_table_[it->second]);
}

}//end namespace Compiler
