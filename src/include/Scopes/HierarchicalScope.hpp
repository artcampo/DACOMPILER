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

class HierarchicalScope : public Scope{
public:
  HierarchicalScope(const ScopeId id
    , Node* const generator
    , const ScopeOwnerId scope_owner_id)
  : Scope(id, generator,scope_owner_id){}

  HierarchicalScope(const ScopeId id, const ScopeOwnerId scope_owner_id)
  : HierarchicalScope(id, nullptr, scope_owner_id){}

  ~HierarchicalScope() = default;

  bool IsDeclValid(const std::string& name){};
  bool HasDecl(const std::string& name){};

  bool RegisterDecl(const std::string& name, const Type& type, const Node& n
      , AST::Symbols::SymbolId symbol_id){};



  std::string str() const noexcept{
    std::string s("hieScope not impl");
    return s;
  }

private:

};


}//end namespace AST
}//end namespace Compiler
