#pragma once
#include <cstddef>

namespace Compiler{
namespace AST{

class TypeId{
public:
  TypeId(){}
  TypeId(size_t id) : id_(id){}

  const bool operator<  ( const TypeId &type_id )const noexcept{
    return id_ < type_id.id_;
  }

  const TypeId& operator=(const TypeId &t ){id_ = t.id_;}
  const bool operator==( const TypeId& t ) const noexcept {return id_ == t.id_;}
private:
  size_t id_;
};

}//end namespace AST
}//end namespace Compiler
