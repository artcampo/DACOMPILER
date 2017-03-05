#pragma once
#include <memory>

namespace Compiler{
namespace AST{


/////////////////////////////////////////////////////////
class FuncDef : public Node {
public:
  virtual ~FuncDef() = default;
  FuncDef(std::string name
    , PtrBlock& body
    , const Type& ret_type
    , std::vector<PtrVarDecl>& par_list
    , const ScopeId id
    , const Locus& locus)
  : Node(id, locus), body_(std::move(body)), name_(name), ret_type_(ret_type)
    , par_list_(std::move(par_list)){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return std::string("FuncDef: ") + name_;}

  Block&    GetBody() const noexcept{ return *body_;}
  const std::string&  Name() const noexcept{ return name_;}

  size_t NumPars()  const noexcept{ return par_list_.size();}
  const std::vector<PtrVarDecl>& ParList()const noexcept{ return par_list_;}
  std::vector<PtrVarDecl>& ParList() noexcept{ return par_list_;}
private:
//   PtrArg
  PtrBlock      body_;
  std::string   name_;
  const Type&   ret_type_;
  std::vector<PtrVarDecl> par_list_;

public:
  /*
  using it_par       = std::vector<PtrVarDecl>::iterator;
  using const_it_par = std::vector<PtrVarDecl>::const_iterator;
  it_par ParBegin() { return par_list_.begin(); }
  it_par ParEnd()   { return par_list_.end(); }
  const_it_par ParBegin()  const { return par_list_.begin(); }
  const_it_par ParEnd()    const { return par_list_.end(); }
  const_it_par ParCbegin() const { return par_list_.cbegin(); }
  const_it_par ParCend()   const { return par_list_.cend(); }
  */
};



}//end namespace AST
}//end namespace Compiler
