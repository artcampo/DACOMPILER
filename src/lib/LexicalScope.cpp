#include "LexicalScope.hpp"

namespace Compiler{
namespace AST{

// using namespace Symbols;

// returns:
// - false if same symbol on same scope was already defined
// - true otherwise
bool LexicalScope::RegDecl(const std::string& name, const Type& type){
  auto it = symbol_table_.find(name);
  Symbols::SymbolId previous_id = -1;
  if(it != symbol_table_.end()){
    previous_id = it->second;
    if(declaration_table_[previous_id].GetScopeId() == GetScopeId())
      return false;
  }

  Symbols::SymbolId id = free_symbol_id_;
  ++free_symbol_id_;

  const Symbols::Symbol symbol = Symbols::Symbol(name, type, GetScopeId());

  symbol_table_[name] = id;
  declaration_table_[id] = symbol;

  //store for deletion when scope is exited
  symbols_.push_back( InsertedSymbol(name, previous_id));
  declarations_.push_back( InsertedDeclarations(id, symbol));
  return true;
}

bool LexicalScope::IsDecl(const std::string& name){
  auto it = symbol_table_.find(name);
  if(it == symbol_table_.end()) return false;
  return true;
}

Type LexicalScope::GetType(const std::string& name){
  const Symbols::SymbolId id = symbol_table_[name];
  return declaration_table_[id].GetType();
}

LexicalScope* LexicalScope::NewNestedScope(const ScopeId id){
  LexicalScope* n = new LexicalScope(id, this, symbol_table_, declaration_table_);
  nested_scopes_.push_back( std::unique_ptr<LexicalScope>(n) );
  return n;
}

void LexicalScope::UndoTables(){
  for(const auto& it : symbols_){
    if(it.second == -1){
      //there was no old symbol name, just delete current one
      symbol_table_.erase( symbol_table_.find(it.first));
    }else{
      //there was an shadowed name, restore its symbol id
      symbol_table_[it.first] = it.second;
    }
  }
  for(const auto& it : declarations_)
    declaration_table_.erase( declaration_table_.find(it.first));

}

}//end namespace AST
}//end namespace Compiler
