#pragma once
#include <map>
#include <cstddef>
#include "Symbol.hpp"

namespace Compiler{
namespace AST{

// using namespace Symbols;

class LexicalScope {
public:
  LexicalScope(LexicalScope* const parent): parent_(parent){}
  LexicalScope(LexicalScope* const parent, Node* const generator)
  : parent_(parent), generator_(generator){}


  LexicalScope* const parent_;
  Node* generator_;

  std::map<Symbols::SymbolString,Symbols::SymbolId> symbol_table_;
  std::map<Symbols::SymbolId,Symbols::Symbol>       declaration_table_;

};


}//end namespace AST
}//end namespace Compiler
