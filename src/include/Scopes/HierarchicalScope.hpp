#pragma once
#include "Scopes/Scope.hpp"

namespace Compiler{
namespace AST{

class HierarchicalScope : public Scope{
public:
  HierarchicalScope(const ScopeId id, const ScopeOwnerId scope_owner_id)
  : Scope(id, scope_owner_id){}

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
