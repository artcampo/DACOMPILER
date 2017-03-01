#pragma once
#include "AST.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include "TypeTable.hpp"
#include "Node.hpp"
#include "Symbol.hpp"
#include "Function.hpp"
#include "IR/Offset.hpp"
#include <map>
#include <memory>

namespace Compiler{
namespace AST{

using AST::Ast;
using AST::Type;
using AST::Node;
using AST::ProgBody;
using AST::ScopeId;
using AST::SymbolTable;
using namespace Compiler::AST::Ptrs;
using AST::FuncDecl;

class Function;
using PtrFunction = std::unique_ptr<Function>;

using OffsetTable = std::map<Symbols::SymbolId, IR::Offset>;

class Function{
public:

  Function(std::string& name, FuncDecl* origin_node
    , OffsetTable& module_offset_table): name_(name)
      , origin_node_(origin_node), module_offset_table_(module_offset_table){}

  Function(std::string& name, OffsetTable& module_offset_table)
    : Function(name, nullptr, module_offset_table){}

  FuncDecl& GetFuncDeclNode() { return *origin_node_; }
  const FuncDecl& GetFuncDeclNode() const { return *origin_node_; }


  Symbols::Symbol& GetSymbolDecl(const Node& n) const{
//     std::cout << "Asking n: " << &n << " " << n.str() << std::endl;
    return *symbol_decl_of_node_.at(&n);
  }

  void StoreDecl(Symbols::Symbol& s, const Node& n){
    symbol_decl_of_node_[&n] = &s;
  }

  void SetOriginNode(FuncDecl& n){
    origin_node_ = &n;
  }

  void StoreSymbolOffset(Symbols::SymbolId id, IR::Offset o){
//     std::cout << "Store: " << id << " o: " << o.str() << std::endl;
    offset_table_[id] = o;
    module_offset_table_[id] = o;
  }

  IR::Offset LocalVarOffset(Symbols::SymbolId id)const{
    return offset_table_.at(id);
  }

private:
  std::string&      name_;
  FuncDecl*         origin_node_;

  OffsetTable&      module_offset_table_;
  OffsetTable       offset_table_;
  std::map<const Node*, Symbols::Symbol*> symbol_decl_of_node_;

};


}//end namespace AST
}//end namespace Compiler
