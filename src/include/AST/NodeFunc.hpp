#pragma once
#include <memory>
#include "AST/Node.hpp"
#include "Types/FuncType.hpp"

namespace Compiler{
namespace AST{

  /////////////////////////////////////////////////////////
class FuncDecl : public Node, public NamedNode, public TypedNode {
public:
  virtual ~FuncDecl() = default;
  FuncDecl(const std::string& name
    , const Type& ret_type
    , std::vector<PtrVarDecl>& par_list
    , const ScopeId id
    , const Locus& locus)
  : Node(id, locus), NamedNode(name), TypedNode(ret_type)
    , par_list_(std::move(par_list)){}


  //FuncDecl cannot be visited
  virtual void Accept(IRGenerator& v, const Node* successor){};
  virtual void Accept(ASTVisitor& v){};

  virtual std::string str() const noexcept { return "FuncDecl: " + name_;}


  const Type&  GetRetType() const noexcept{ return GetType(); }

  size_t NumPars()  const noexcept{ return par_list_.size();}
  const std::vector<PtrVarDecl>& ParList()const noexcept{ return par_list_;}
  std::vector<PtrVarDecl>& ParList() noexcept{ return par_list_;}
private:
  std::vector<PtrVarDecl> par_list_;

public:
  /*
   //TODO: use these again!
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

/////////////////////////////////////////////////////////
class FuncDef : public Node, public NamedNode {
public:
  virtual ~FuncDef() = default;
  FuncDef(PtrFuncDecl& decl
    , PtrBlock& body
    , const ScopeId id
    , const Locus& locus)
  : Node(id, locus), body_(std::move(body)), decl_(std::move(decl))
    , NamedNode(decl->Name()){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return "FuncDef: " + Name();}

  Block&    GetBody() const noexcept{ return *body_;}
  const Type&  GetRetType() const noexcept{ return decl_->GetRetType();}

  size_t NumPars()  const noexcept{ return decl_->NumPars();}
  const std::vector<PtrVarDecl>& ParList() const noexcept{ return decl_->ParList();}
  std::vector<PtrVarDecl>& ParList() noexcept{ return decl_->ParList();}
private:
//   PtrArg
  PtrBlock      body_;
  PtrFuncDecl   decl_;

public:
  /*
   //TODO: use these again!
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

/////////////////////////////////////////////////////////
//Provides range-for iteration over its arg expressions
//accepts as call target any ExprVar
class FuncCall: public Node, public NamedNode, public TypedNode {
public:
  virtual ~FuncCall() = default;
  FuncCall(const std::string& name
    , PtrExprVar& receiver
    , const FuncType& function_type
    , std::vector<PtrExpr>& arg_list
    , const ScopeId id
    , const Locus& locus)
  : Node(id, locus), NamedNode(name)
    , TypedNode(dynamic_cast<const Type&>(function_type))
    , receiver_(std::move(receiver))
    , arg_list_(std::move(arg_list)){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return "FuncCall: " + receiver_->str();}

  size_t NumArgs()  const noexcept{ return arg_list_.size();}

  ExprVar& Receiver() const noexcept{ return *receiver_;}

  const FuncType& GetType() const noexcept{
    return dynamic_cast<const FuncType&>(TypedNode::GetType());
  }
  void SetType(const FuncType& function_type) noexcept{
    TypedNode::SetType( dynamic_cast<const Type&>(function_type));
  }
private:
  PtrExprVar            receiver_;
  std::vector<PtrExpr>  arg_list_;

public:

  using iterator       = std::vector<PtrExpr>::iterator;
  using const_iterator = std::vector<PtrExpr>::const_iterator;
  iterator begin() { return arg_list_.begin(); }
  iterator end()   { return arg_list_.end(); }
  const_iterator begin()  const { return arg_list_.begin(); }
  const_iterator end()    const { return arg_list_.end(); }
  const_iterator cbegin() const { return arg_list_.cbegin(); }
  const_iterator cend()   const { return arg_list_.cend(); }
};

/////////////////////////////////////////////////////////
class FuncRet: public ExprVar, public TypedNode {
public:
  virtual ~FuncRet() = default;
  FuncRet(const Type& ret_type
    , PtrFuncCall& call
    , const ScopeId id
    , const Locus& locus)
  : ExprVar(id, locus), TypedNode(ret_type)
    , call_(std::move(call)){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return "FuncRet: " + GetType().str();}

  FuncCall&    GetCall() const noexcept{ return *call_;}
private:

  PtrFuncCall call_;
};


}//end namespace AST
}//end namespace Compiler
