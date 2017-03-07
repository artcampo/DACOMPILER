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
  const Type&  GetRetType() const noexcept{ return ret_type_;}

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
class FuncCall: public Node {
public:
  virtual ~FuncCall() = default;
  FuncCall(const std::string& name
    , const FuncType& function_type
    , std::vector<PtrExpr>& arg_list
    , const ScopeId id
    , const Locus& locus)
  : Node(id, locus), name_(name), function_type_(function_type)
    , arg_list_(std::move(arg_list)){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return std::string("FuncCall: ") + name_;}

  const std::string&  Name() const noexcept{ return name_;}
  size_t NumArgs()  const noexcept{ return arg_list_.size();}

  const FuncType& GetType()const noexcept{return function_type_;}
private:
  std::string   name_;
  const FuncType&   function_type_;
  std::vector<PtrExpr> arg_list_;

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
class FuncRet: public Expr {
public:
  virtual ~FuncRet() = default;
  FuncRet(const Type& ret_type
    , PtrFuncCall& call
    , const ScopeId id
    , const Locus& locus)
  : Expr(id, locus), ret_type_(ret_type)
    , call_(std::move(call)){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return "FuncRet: " + ret_type_.str();}

  FuncCall&    GetCall() const noexcept{ return *call_;}
  const Type& GetType()const noexcept{return ret_type_;}
private:

  const Type&   ret_type_;
  PtrFuncCall   call_;
};


}//end namespace AST
}//end namespace Compiler
