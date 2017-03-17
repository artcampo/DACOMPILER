#pragma once
#include <memory>
#include "AST/Node.hpp"

namespace Compiler{
namespace AST{


/////////////////////////////////////////////////////////
class VarDeclList : public Node{
public:

  virtual ~VarDeclList() = default;
  /*
  VarDeclList(std::vector<PtrVarDecl>& list, const ScopeId id
            , const Locus& locus)
    : Node(id, locus)
    {for (auto& it : list) list_.push_back(std::move(it));}
    */
  VarDeclList(std::vector<PtrVarDecl>& list, const ScopeId id
            , const Locus& locus)
    : Node(id, locus), list_(std::move(list)){}

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);

  std::vector<PtrVarDecl>& GetVarDeclVector() noexcept{return list_;};
  const std::vector<PtrVarDecl>& GetVarDeclVector() const noexcept{return list_;};
  virtual std::string str() const;

  using iterator       = std::vector<PtrVarDecl>::iterator;
  using const_iterator = std::vector<PtrVarDecl>::const_iterator;
  iterator begin() { return list_.begin(); }
  iterator end()   { return list_.end(); }
  const_iterator begin()  const { return list_.begin(); }
  const_iterator end()    const { return list_.end(); }
  const_iterator cbegin() const { return list_.cbegin(); }
  const_iterator cend()   const { return list_.cend(); }
private:
  std::vector<PtrVarDecl> list_;
};

/////////////////////////////////////////////////////////
class VarDecl : public Node, public NamedNode, public TypedNode{
public:
  virtual ~VarDecl() = default;
  VarDecl(const std::string& name, const Type& type, const ScopeId id
    , const Locus& locus)
    : Node(id, locus), NamedNode(name), TypedNode(type){}

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
  std::string str() const noexcept{ return  GetType().str() + " " + name_;}
};



}//end namespace AST
}//end namespace Compiler
