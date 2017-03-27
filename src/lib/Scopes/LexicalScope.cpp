#include "Scopes/LexicalScope.hpp"
 #include <iostream>

namespace Compiler{
namespace AST{

// using namespace Symbols;

// returns:
// - false if same symbol on same scope was already defined
// - true otherwise
bool LexicalScope::RegisterDecl(const std::string& name, const Type& type
  ,  const Node& n, AST::Symbols::SymbolId symbol_id){
  auto it = symbol_table_.find(name);
  Symbols::SymbolId previous_id = -1;
  if(it != symbol_table_.end()){
    previous_id = it->second;
    if(declaration_table_[previous_id]->GetScopeId() == GetScopeId())
      return false;
  }

  symbol_table_[name] = symbol_id;
  declaration_table_[symbol_id] = std::make_unique<Symbols::Symbol>
                              (name, type, GetScopeId(), symbol_id);
  symbolid_of_node_[&n] = symbol_id;

  //store for deletion when scope is exited
  symbols_.push_back( InsertedSymbol(name, previous_id));
  declarations_.push_back( InsertedDeclarations(symbol_id, *declaration_table_[symbol_id]));

  //store for post parse
  post_parse_symbol_table_[name] = symbol_id;
  post_parse_declaration_table_[symbol_id] = std::make_unique<Symbols::Symbol>
                              (name, type, GetScopeId(), symbol_id);  
  /*
  std::cout << "symbol table:";
  for(const auto& it : symbol_table_)
    std::cout << it.first<< " : "<<it.second << "\n";
  std::cout << "decl table:";
  for(const auto& it : declaration_table_)
    std::cout << it.first<< " : "<<it.second->str() << "\n";
  std::cout<< "\n";
  */
  return true;
}

bool LexicalScope::IsDeclValid(const std::string& name){
  auto it = symbol_table_.find(name);
  Symbols::SymbolId previous_id = -1;
  if(it != symbol_table_.end()){
    previous_id = it->second;
    if(declaration_table_[previous_id]->GetScopeId() == GetScopeId())
      return false;
  }
  return true;
}

bool LexicalScope::HasDecl(const std::string& name){
  auto it = symbol_table_.find(name);
  if(it == symbol_table_.end()) return false;
  return true;
}

const Symbols::SymbolId LexicalScope::DeclId(const std::string& name) const{
  auto it = symbol_table_.find(name);
  return it->second;
}
/*
const Type& LexicalScope::GetType(const std::string& name){
  const Symbols::SymbolId id = symbol_table_[name];
  return declaration_table_[id]->GetType();
}
*/
LexicalScope* LexicalScope::NewNestedScope(const ScopeId id
    , const ScopeOwnerId scope_owner_id){

  LexicalScope* n = new LexicalScope(id, this, scope_owner_id, symbol_table_
            , declaration_table_, symbolid_of_node_);
  nested_scopes_.push_back( std::unique_ptr<LexicalScope>(n) );
  return n;
}

void LexicalScope::UndoTables(){
  /*
  std::cout << "symbol table:";
  for(const auto& it : symbol_table_)
    std::cout << it.first<< " : "<<it.second << "\n";
  std::cout << "decl table:";
  for(const auto& it : declaration_table_)
    std::cout << it.first<< " : "<<it.second->str() << "\n";
  std::cout<< "\n";
*/
//   std::cout << "Undo: " << symbols_.size() << std::endl;
  for(const auto& it : symbols_){
//     std::cout << it.first;
    if(it.second == -1){
      //there was no old symbol name, just delete current one
      symbol_table_.erase( symbol_table_.find(it.first));
    }else{
      //there was an shadowed name, restore its symbol id
      symbol_table_[it.first] = it.second;
    }
  }


//  Declarations are always kept
//   for(const auto& it : declarations_){
//
//     auto itdec = declaration_table_.find(it.first);
//     if(itdec == declaration_table_.end()){
//       std::cout << "not found";
//     }
//     declaration_table_.erase(itdec);
//   }

}

}//end namespace AST
}//end namespace Compiler
