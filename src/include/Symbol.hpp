#pragma once
#include <map>
#include <cstddef>
#include "Types.hpp"

namespace Compiler{
namespace AST{

class Node;

namespace Symbols{

using SymbolString = std::string;
using SymbolId     = size_t;

class Symbol {
public:
  Symbol(){}
  Symbol(const SymbolString& name, const TypeId& type)
    :name_(name), type_(type){}

  const bool operator< ( const Symbol &s ) const{
    if( name_ == s.name_) return type_ < s.type_;
    else                  return name_ < s.name_;
  }

  Symbol& operator= ( const Symbol &s ){
    name_ = s.name_;
    type_ = s.type_;
  }

  TypeId GetTypeId() const noexcept{return type_;}

private:
  SymbolString name_;
  TypeId       type_;
};


}//end namespace Symbols
}//end namespace AST
}//end namespace Compiler
