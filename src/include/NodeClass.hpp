#pragma once
#include <memory>

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

//   virtual void Accept(IRGenerator& v, const Node* successor);
//   virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return "ClassDef: " + name_;}


  const std::string&  Name() const noexcept{ return name_;}
private:
  std::string name_;


};




}//end namespace AST
}//end namespace Compiler
