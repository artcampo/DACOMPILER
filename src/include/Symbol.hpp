#pragma once
#include <map>
#include <cstddef>
#include "Types.hpp"
#include "ScopeId.hpp"

namespace Compiler{
namespace AST{

class Node;

namespace Symbols{

using SymbolString = std::string;
using SymbolId     = int;

class Symbol {
public:
//   Symbol(){}
  Symbol(const SymbolString& name, const Type& type, const ScopeId scope_id)
    :name_(name), type_(type), scope_id_(scope_id){}

  const bool operator< ( const Symbol &s ) const{
    if( name_ == s.name_) return type_ < s.type_;
    else                  return name_ < s.name_;
  }

  /*
  Symbol& operator= ( const Symbol &s ){
    name_     = s.name_;
    type_     = s.type_;
    scope_id_ = s.scope_id_;
  }*/

  const Type& GetType() const noexcept{return type_;}
//   Type& GetType() noexcept{return type_;}
  ScopeId GetScopeId() const noexcept{return scope_id_;}

private:
  SymbolString  name_;
  const Type&   type_;
  ScopeId       scope_id_;
};


}//end namespace Symbols
}//end namespace AST
}//end namespace Compiler
