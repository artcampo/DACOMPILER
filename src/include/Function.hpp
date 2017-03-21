#pragma once
#include "AST/AST.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include "AST/Node.hpp"
#include "Symbol.hpp"
#include "Module/TypeTable.hpp"
#include "IR/Offset.hpp"
#include "IR/Label.hpp"
#include <map>
#include <memory>

namespace Compiler{
namespace AST{

using AST::Ast;
using AST::Type;
using AST::Node;
using AST::ProgBody;
using AST::ScopeId;
using namespace Compiler::AST::Ptrs;
using AST::FuncDef;
using IR::Label;

class Function;
using PtrFunction = std::unique_ptr<Function>;

using OffsetTable = std::map<Symbols::SymbolId, IR::Offset>;

class Function{
public:
  static PtrFunction NewFunction(const std::string& name, OffsetTable& module_offset_table
    , const ScopeOwnerId scope_owner_id, const Label entry_label
    , const Label locals_label){
    return std::move( std::make_unique<Function>
      (name, "", name, module_offset_table, scope_owner_id, entry_label
      , locals_label, false));
  }

  static PtrFunction NewMemberFunction(const std::string& name
    , const std::string& class_name
    , OffsetTable& module_offset_table
    , const ScopeOwnerId scope_owner_id, const Label entry_label
    , const Label locals_label){
    return std::move( std::make_unique<Function>
      (name, class_name, MangledName(name, class_name), module_offset_table
      , scope_owner_id, entry_label, locals_label, true));
  }

  static std::string MangledName(const std::string& name
    , const std::string& class_name){
    return class_name + "::" + name;
  }

  FuncDef& GetFuncDefNode() { return *origin_node_; }
  const FuncDef& GetFuncDefNode() const { return *origin_node_; }


  Symbols::Symbol& GetSymbolDecl(const Node& n) const{
//     std::cout << "Asking n: " << &n << " " << n.str() << std::endl;
    return *symbol_decl_of_node_.at(&n);
  }

  void StoreDecl(Symbols::Symbol& s, const Node& n){
    symbol_decl_of_node_[&n] = &s;
  }

  void SetOriginNode(const FuncDef& n){
    origin_node_ = const_cast<FuncDef*>(&n);
  }

  void StoreSymbolOffset(Symbols::SymbolId id, IR::Offset o){
//     std::cout << "Store: " << id << " o: " << o.str() << std::endl;
    offset_table_[id] = o;
    module_offset_table_[id] = o;
  }

  IR::Offset LocalVarOffset(Symbols::SymbolId id)const{
    return offset_table_.at(id);
  }

  const Label      EntryLabel() const noexcept{ return entry_label_;}
  const Label      LocalsLabel() const noexcept{ return locals_label_;}

  std::string str()  const noexcept{ return name_;}

  std::string MangledName()const noexcept{ return mangled_name_;}
  const bool IsMember() const noexcept{ return is_member_;}
  std::string Name()  const noexcept{ return name_;}
private:
  ScopeOwnerId      scope_owner_id_;
  std::string       name_;
  std::string       mangled_name_;
  std::string       class_name_;
  FuncDef*          origin_node_;
  const Label       entry_label_;
  const Label       locals_label_;
  bool              is_member_;


  OffsetTable&      module_offset_table_;
  OffsetTable       offset_table_;
  std::map<const Node*, Symbols::Symbol*> symbol_decl_of_node_;

public:
  Function(const std::string& name
    , const std::string& class_name
    , const std::string& mangled_name
    , OffsetTable& module_offset_table
    , const ScopeOwnerId scope_owner_id, const Label entry_label
    , const Label locals_label, const bool is_member)
  : name_(name)
    , class_name_(class_name)
    , origin_node_(nullptr)
    , module_offset_table_(module_offset_table)
    , scope_owner_id_(scope_owner_id)
    , entry_label_(entry_label)
    , locals_label_(locals_label)
    , is_member_ (is_member)
    , mangled_name_(mangled_name){}

};


}//end namespace AST
}//end namespace Compiler
