#pragma once
#include <map>
#include <cstddef>
#include "Types.hpp"
#include "Scopes/ScopeId.hpp"

namespace Compiler{
namespace AST{

class Node;

namespace Symbols{

using SymbolString = std::string;
// using SymbolId     = int;

class SymbolId{
public:
  SymbolId(){}
  SymbolId(const int id) : id_(id){}

  const bool operator<  ( const SymbolId &type_id )const noexcept{
    return id_ < type_id.id_;
  }

  const SymbolId& operator=(const SymbolId &t ){id_ = t.id_;}
  const bool operator==( const SymbolId& t ) const noexcept {return id_ == t.id_;}
  const bool operator==( const int t ) const noexcept {return id_ == t;}

  SymbolId& operator++(){++id_; return *this;}
  SymbolId operator++(int){ SymbolId copy(*this);++(*this); return copy;}
  operator int() const { return id_; }

private:
  int id_;
};

class Symbol {
public:
//   Symbol(){}
  Symbol(const SymbolString name, const Type& type, const ScopeId scope_id
    , const SymbolId id)
    :name_(name), type_(type), scope_id_(scope_id), id_(id){}

  const bool operator< ( const Symbol &s ) const{
    if( name_ == s.name_) return type_ < s.type_;
    else                  return name_ < s.name_;
  }

  Symbol& operator= ( const Symbol &s ) = delete;
  Symbol( const Symbol &s ) = delete;
  /*
  Symbol& operator= ( const Symbol &s ){
    name_     = s.name_;
    type_     = s.type_;
    scope_id_ = s.scope_id_;
  }*/

  static const SymbolId UnknownSymbol() {return 0;}
  static const SymbolId InitialFreeId() {return 1;}


  const SymbolId Id() const noexcept {return id_;}

  const Type& GetType() const noexcept{return type_;}
//   Type& GetType() noexcept{return type_;}
  ScopeId GetScopeId() const noexcept{return scope_id_;}
  size_t Size() const noexcept{ return type_.Size();}

  std::string str() const noexcept{
    return std::string("Symbol: [")
      + " in scope " + std::to_string(scope_id_)
      + " " + name_
      + " of type " + type_.str()
      + std::string("]");
  }

  std::string BareName() const noexcept{ return name_; }

private:
  SymbolString  name_;
  const Type&   type_;
  ScopeId       scope_id_;
  SymbolId      id_;
};


}//end namespace Symbols
}//end namespace AST
}//end namespace Compiler
