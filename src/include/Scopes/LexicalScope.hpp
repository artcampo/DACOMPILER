#pragma once
#include "Scopes/Scope.hpp"

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

class LexicalScope : public Scope {
public:
  LexicalScope(const ScopeId id, LexicalScope* const parent
    , const ScopeOwnerId scope_owner_id
    , SymbolTable& symbol_table
    , DeclarationTable& declaration_table
    , SymbolIdOfNode& symbolid_of_node)
  : Scope(id, scope_owner_id), parent_(parent)
    , symbol_table_(symbol_table), declaration_table_(declaration_table)
    , symbolid_of_node_(symbolid_of_node){}


  virtual ~LexicalScope() = default;

  bool IsDeclValid(const std::string& name);
  bool HasDecl(const std::string& name);

  bool RegisterDecl(const std::string& name, const Type& type, const Node& n
      , AST::Symbols::SymbolId symbol_id);

//   const Type& GetType(const std::string& name) const;
  const Symbols::SymbolId DeclId(const std::string& name) const;

  LexicalScope* NewNestedScope(const ScopeId id
                              , const ScopeOwnerId scope_owner_id);
  LexicalScope* GetParentScope() const noexcept{return parent_;};

  virtual const Type& GetType(const std::string& name) const override{
    const Symbols::SymbolId sid = DeclId(name);
    return declaration_table_.at(sid)->GetType();
  }

  void UndoTables();

  std::string str() const noexcept{
    std::string s = std::string("Scope ") + std::to_string(id_)
                  + std::string(": {");
    for(int i = 0; i < declarations_.size(); ++i){
      s+= "(" + std::to_string(declarations_[i].first) + ":";
      s+= symbols_[i].first + ") ";
    }
    s += std::string("}");
    return s;
  }

  //Post parse use
  virtual const Type& PostGetType(const std::string& name) const{
    const Symbols::SymbolId sid = PostDeclId(name);
    return post_parse_declaration_table_.at(sid)->GetType();
  }  
  
  const Symbols::SymbolId PostDeclId(const std::string& name) const {
    auto it = post_parse_symbol_table_.find(name);
    return it->second;
  }

private:
  LexicalScope* parent_;
  std::vector<PtrLexicalScope> nested_scopes_;

  std::vector<InsertedSymbol> symbols_;
  std::vector<InsertedDeclarations> declarations_;


  //these are refence to function
  SymbolTable&      symbol_table_;
  DeclarationTable& declaration_table_;
  SymbolIdOfNode&   symbolid_of_node_;
  
  //these are local copies to consult when parsing is done
  SymbolTable       post_parse_symbol_table_;
  DeclarationTable  post_parse_declaration_table_;

};


}//end namespace AST
}//end namespace Compiler
