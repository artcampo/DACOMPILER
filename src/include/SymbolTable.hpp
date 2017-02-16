#pragma once
#include "Symbol.hpp"

namespace Compiler{
namespace AST{


using SymbolTable = std::map<Symbols::SymbolString,Symbols::SymbolId>;
using DeclarationTable = std::map<Symbols::SymbolId,Symbols::Symbol>;

}//end namespace AST
}//end namespace Compiler
