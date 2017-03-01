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

  Function(std::string& name, FuncDecl* origin_node): name_(name)
    , origin_node_(origin_node){}

  Function(std::string& name): Function(name, nullptr){}

  FuncDecl& GetFuncDeclNode() { return *origin_node_; }
  const FuncDecl& GetFuncDeclNode() const { return *origin_node_; }


  Symbols::Symbol& GetSymbolDecl(const Node& n){

  }
  void SetOriginNode(FuncDecl& n){
    origin_node_ = &n;
  }


private:
  std::string&      name_;
  FuncDecl*         origin_node_;
  OffsetTable       offset_table_;

};


}//end namespace AST
}//end namespace Compiler
