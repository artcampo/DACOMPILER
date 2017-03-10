#pragma once
#include <memory>
#include "AST/Node.hpp"

namespace Compiler{
namespace AST{


/////////////////////////////////////////////////////////
class ClassDef : public Node {
public:
  virtual ~ClassDef() = default;
  ClassDef(const std::string& name
    , const ScopeId id
    , const Locus& locus)
  : Node(id, locus), name_(name){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return "ClassDef: " + name_;}


  const std::string&  Name() const noexcept{ return name_;}
private:
  std::string name_;


};

/////////////////////////////////////////////////////////
// This is mean to te the Rhs of the dot operator
class VarName : public Node{
public:
  virtual ~VarName() = default;
  VarName(const std::string& name, const ScopeId scope_id , const Locus& locus)
    : Node(scope_id, locus), name_(name){}


  std::string str() const noexcept{return name_;}

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
private:
  const std::string name_;

};



}//end namespace AST
}//end namespace Compiler
