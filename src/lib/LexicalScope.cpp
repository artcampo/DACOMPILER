#include "LexicalScope.hpp"

namespace Compiler{
namespace AST{

// using namespace Symbols;


bool LexicalScope::RegDecl(const std::string& name, const TypeId& type){
  auto it = symbol_table_.find(name);
  if(it != symbol_table_.end()) return false;

  Symbols::SymbolId id = free_symbol_id_;
  ++free_symbol_id_;

  symbol_table_[name] = id;
  declaration_table_[id] = Symbols::Symbol(name, type);
  return true;
}

bool LexicalScope::IsDecl(const std::string& name){
  auto it = symbol_table_.find(name);
  if(it == symbol_table_.end()) return false;
  return true;
}

TypeId LexicalScope::GetTypeId(const std::string& name){
  const Symbols::SymbolId id = symbol_table_[name];
  return declaration_table_[id].GetTypeId();
}

LexicalScope* LexicalScope::NewNestedScope(const ScopeId id){
  LexicalScope* n = new LexicalScope(id, this);
  nested_scopes_.push_back( std::unique_ptr<LexicalScope>(n) );
  return n;
}

}//end namespace AST
}//end namespace Compiler
