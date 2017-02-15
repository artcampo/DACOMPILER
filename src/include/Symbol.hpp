#pragma once
#include <map>
#include <cstddef>

namespace Compiler{
namespace AST{

class Node;

namespace Symbols{

using SymbolString = std::string;
using SymbolId     = size_t;

class Symbol {
public:
  Symbol(const SymbolString& name, const TypeId& type)
    :name_(name), type_(type){}

  const SymbolString name_;
  const TypeId       type_;



};


}//end namespace Symbols
}//end namespace AST
}//end namespace Compiler
