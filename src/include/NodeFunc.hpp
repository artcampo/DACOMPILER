#pragma once
#include <memory>

namespace Compiler{
namespace AST{


/////////////////////////////////////////////////////////
class FuncDef : public Node {
public:
  virtual ~FuncDef() = default;
  FuncDef(std::string name, PtrBlock& body
    , const Type& ret_type
    , const ScopeId id
    , const Locus& locus)
  : Node(id, locus), body_(std::move(body)), name_(name), ret_type_(ret_type)
  , id_(sid){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return std::string("FuncDef: ") + name_;}

  Block&    GetBody() const noexcept{ return *body_;}
private:
//   PtrArg
  PtrBlock      body_;
  std::string   name_;
  const Type&   ret_type_;
};



}//end namespace AST
}//end namespace Compiler
