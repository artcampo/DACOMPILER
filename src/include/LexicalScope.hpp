#pragma once
#include <map>
#include <cstddef>
#include <memory>
#include <vector>
#include "Symbol.hpp"
#include "Types.hpp"
#include "ScopeId.hpp"
#include "SymbolTable.hpp"

/*
 * Resolving a current's scope symbol revolves around checking current and
 * parent scopes. That can be collapsed into having a single symbol table,
 * where each time we leave a scope, we delete the symbols inserted within.
 * Thus having the global symbol table at each point of parsing.
 *
 * For verification pourposes it's interesting to have the list of symbols
 * that belong to each scope. Coincidently the stack of symbols to remove
 * after closing this scope has exactly this information. Thus we keep it,
 * which we wouldn't do if we were not to verify the execution.
 */

namespace Compiler{
namespace AST{

// using namespace Symbols;
using ScopeId = size_t;
//pair of name and symbol that was shadowed (or -1 if none)
using InsertedSymbol = std::pair<Symbols::SymbolString, Symbols::SymbolId>;
using InsertedDeclarations = std::pair<Symbols::SymbolId, Symbols::Symbol&>;
using SymbolIdOfNode = std::map<const Node*, Symbols::SymbolId>;

class LexicalScope;
using PtrLexicalScope = std::unique_ptr<LexicalScope>;


class LexicalScope {
public:
  LexicalScope(const ScopeId id, LexicalScope* const parent
    , SymbolTable& symbol_table
    , DeclarationTable& declaration_table
    , SymbolIdOfNode& symbolid_of_node)
  : id_(id), parent_(parent)
  , symbol_table_(symbol_table), declaration_table_(declaration_table)
  , symbolid_of_node_(symbolid_of_node){}

  LexicalScope(const ScopeId id, LexicalScope* const parent
    , Node* const generator
    , SymbolTable& symbol_table
    , DeclarationTable& declaration_table
    , SymbolIdOfNode& symbolid_of_node)
  : id_(id), parent_(parent), generator_(generator)
  , symbol_table_(symbol_table), declaration_table_(declaration_table)
  , symbolid_of_node_(symbolid_of_node){}

  bool IsDeclValid(const std::string name, const Type& type);
  bool RegisterDecl(const std::string name, const Type& type, const Node& n
      , AST::Symbols::SymbolId symbol_id);
  bool IsDecl(const std::string& name);
  const Type& GetType(const std::string& name);
  const Symbols::SymbolId DeclId(const std::string& name) const;
  const ScopeId GetScopeId() const noexcept{return id_;};

  LexicalScope* NewNestedScope(const ScopeId id);
  LexicalScope* GetParentScope() const noexcept{return parent_;};

  void UndoTables();

  std::string str() const noexcept{
    std::string s = std::string("Scope ") + std::to_string(id_)
                  + std::string(": {");
    for(int i = 0; i < declarations_.size(); ++i){
      s+= std::to_string(declarations_[i].first) + std::string(", ");
      s+= symbols_[i].first + std::string(" ");

    }
    s += std::string("}");
    return s;
  }

private:
  ScopeId       id_;
  LexicalScope* parent_;
  Node*         generator_;
  std::vector<PtrLexicalScope> nested_scopes_;

  std::vector<InsertedSymbol> symbols_;
  std::vector<InsertedDeclarations> declarations_;


  //these are refence to function
  SymbolTable&      symbol_table_;
  DeclarationTable& declaration_table_;
  SymbolIdOfNode&   symbolid_of_node_;

};


}//end namespace AST
}//end namespace Compiler
