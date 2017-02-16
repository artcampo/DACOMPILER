#pragma once
#include <map>
#include <cstddef>
#include <memory>
#include <vector>
#include "Symbol.hpp"
#include "Types.hpp"
#include "ScopeId.hpp"

namespace Compiler{
namespace AST{

// using namespace Symbols;
using ScopeId = size_t;

class LexicalScope {
public:
  LexicalScope(const ScopeId id, LexicalScope* const parent)
  : id_(id), parent_(parent), free_symbol_id_(0){}

  LexicalScope(const ScopeId id, LexicalScope* const parent, Node* const generator)
  : id_(id), parent_(parent), generator_(generator), free_symbol_id_(0){}

  bool RegDecl(const std::string& name, const TypeId& type);
  bool IsDecl(const std::string& name);
  TypeId GetTypeId(const std::string& name);
  const ScopeId GetScopeId() const noexcept{return id_;};

  LexicalScope* NewNestedScope(const ScopeId id);
  LexicalScope* GetParentScope() const noexcept{return parent_;};

  std::string str() const noexcept{
    std::string s = std::string("Scope ") + std::to_string(id_)
                  + std::string(": {");
    for(auto it : symbol_table_){
      s+= std::to_string(it.second) + std::string(", ");
      s+= it.first + std::string(" ");
    }
    s += std::string("}");
    return s;
  }

private:
  ScopeId       id_;
  LexicalScope* parent_;
  Node*         generator_;

  std::map<Symbols::SymbolString,Symbols::SymbolId> symbol_table_;
  std::map<Symbols::SymbolId,Symbols::Symbol>       declaration_table_;
  std::vector<std::unique_ptr<LexicalScope> >       nested_scopes_;

  Symbols::SymbolId free_symbol_id_;

};


}//end namespace AST
}//end namespace Compiler
