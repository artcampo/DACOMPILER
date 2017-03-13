#pragma once
#include <map>
#include <cstddef>
#include <memory>
#include <vector>
#include "Symbol.hpp"
#include "Types.hpp"
#include "Scopes/ScopeId.hpp"
#include "SymbolTable.hpp"


namespace Compiler{
namespace AST{

// using namespace Symbols;
using ScopeId = size_t;
using ScopeOwnerId = size_t;
//pair of name and symbol that was shadowed (or -1 if none)
using InsertedSymbol = std::pair<Symbols::SymbolString, Symbols::SymbolId>;
using InsertedDeclarations = std::pair<Symbols::SymbolId, Symbols::Symbol&>;
using SymbolIdOfNode = std::map<const Node*, Symbols::SymbolId>;

class LexicalScope;
using PtrLexicalScope = std::unique_ptr<LexicalScope>;


class Scope {
public:
  Scope(const ScopeId id, Node* const generator
    , const ScopeOwnerId scope_owner_id)
  : id_(id), generator_(generator), scope_owner_id_(scope_owner_id){}

  Scope(const ScopeId id, const ScopeOwnerId scope_owner_id)
  : Scope(id, nullptr, scope_owner_id){}

  virtual ~Scope() = default;

  virtual bool IsDeclValid(const std::string& name) = 0;
  virtual bool HasDecl(const std::string& name) = 0;

  virtual bool RegisterDecl(const std::string& name, const Type& type, const Node& n
      , AST::Symbols::SymbolId symbol_id) = 0;

  virtual std::string str() const noexcept = 0;


  const ScopeId GetScopeId() const noexcept{return id_;};
  const ScopeOwnerId GetScopeOwnerId() const noexcept{ return scope_owner_id_;}

protected:
  ScopeId       id_;
  ScopeOwnerId  scope_owner_id_;
  Node*         generator_;

};


}//end namespace AST
}//end namespace Compiler
