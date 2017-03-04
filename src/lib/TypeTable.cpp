#include "TypeTable.hpp"

namespace Compiler{

const Type& TypeTable::GetType(const kBasicTypeId basic_id){
  const TypeId& type_id = GetTypeId(basic_id);
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


}//end namespace Compiler
