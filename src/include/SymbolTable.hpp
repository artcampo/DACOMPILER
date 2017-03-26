#pragma once
#include "Symbol.hpp"
#include <memory>

namespace Compiler{
namespace AST{


using SymbolTable =
  std::map<Symbols::SymbolString,Symbols::SymbolId>;

using SymbolTableIt = std::map<Symbols::SymbolString,Symbols::SymbolId>::iterator;
using SymbolTableItC = std::map<Symbols::SymbolString,Symbols::SymbolId>::const_iterator;
  
using DeclarationTable =
  std::map<Symbols::SymbolId, std::unique_ptr<Symbols::Symbol>>;

}//end namespace AST
}//end namespace Compiler
