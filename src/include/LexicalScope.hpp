#pragma once
#include <map>
#include <cstddef>
#include "Symbol.hpp"
#include "Types.hpp"

namespace Compiler{
namespace AST{

// using namespace Symbols;

class LexicalScope {
public:
  LexicalScope(LexicalScope* const parent): parent_(parent), free_id_(0){}
  LexicalScope(LexicalScope* const parent, Node* const generator)
  : parent_(parent), generator_(generator), free_id_(0){}

  bool RegDecl(const std::string& name, const TypeId& type);
  bool IsDecl(const std::string& name);
  TypeId GetTypeId(const std::string& name);
private:
  LexicalScope* const parent_;
  Node* generator_;

  std::map<Symbols::SymbolString,Symbols::SymbolId> symbol_table_;
  std::map<Symbols::SymbolId,Symbols::Symbol>       declaration_table_;

  Symbols::SymbolId free_id_;

};


}//end namespace AST
}//end namespace Compiler
