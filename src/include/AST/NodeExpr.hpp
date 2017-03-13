#pragma once
#include <memory>
#include "Symbol.hpp"

#include "Scopes/ScopeId.hpp"
#include "AST/Node.hpp"

namespace Compiler{
namespace AST{


//
class ExprVar : public Expr {
public:
  virtual ~ExprVar() = default;
  ExprVar(const ScopeId id, const Locus& locus) : Expr(id, locus){}
  std::string str() const noexcept = 0;
};

/////////////////////////////////////////////////////////
class Literal : public Expr {
public:
  virtual ~Literal() = default;
  Literal(const uint32_t &value, const Type& type, const ScopeId id
    , const Locus& locus)
    : Expr(id, locus), value_(value), type_(type){}

  const Type& GetType()const noexcept{return type_;}
  uint32_t Value() const noexcept{ return value_;};

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
  std::string str() const noexcept{return std::to_string(value_);}

private:
  const Type&  type_;
  //todo: uint32_t->NodeValue
  uint32_t  value_;
};


/////////////////////////////////////////////////////////
class BinaryOp : public Expr {
public:
  virtual ~BinaryOp() = default;
  int op;
  //TODO change op to own type
  BinaryOp(PtrExpr& lhs, const int op, PtrExpr& rhs, const ScopeId id
    , const Locus& locus)
    : Expr(id, locus), lhs_(std::move(lhs)), rhs_(std::move(rhs)), op(op){}

  Expr& Lhs() const noexcept{return *lhs_;}
  Expr& Rhs() const noexcept{return *rhs_;}

  //TODO: merge these
  std::string OpString() const noexcept;
  std::string str() const noexcept{return OpString();}

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
private:
  PtrExpr lhs_;
  PtrExpr rhs_;
};


/////////////////////////////////////////////////////////
class Var : public ExprVar{
public:
  virtual ~Var() = default;
  Var(const std::string& name, const Type& type, Symbols::SymbolId id
    , const ScopeId scope_id , const Locus& locus)
    : ExprVar(scope_id, locus), name_(name),type_(type), id_(id){}

  const Type& GetType()const noexcept{return type_;}
  std::string str() const noexcept{return name_;}

  Symbols::SymbolId Id() const noexcept{return id_;}
  const std::string&  Name() const noexcept{ return name_;}

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
private:
  const std::string name_;
  const Type&  type_;
  Symbols::SymbolId id_;
};

/////////////////////////////////////////////////////////
class UnaryOp  {
public:
  //UnaryOp()   = default;
  ~UnaryOp()  = default;

  UnaryOp(PtrExpr& rhs) :  rhs_(std::move(rhs)){}

  virtual Expr& Rhs() const noexcept {return *rhs_;}

private:
  PtrExpr rhs_;
};

/////////////////////////////////////////////////////////
class RefOp : public Expr, public UnaryOp {
public:

  virtual ~RefOp() = default;
  //TODO change op to own type
  RefOp(PtrExpr& rhs, const ScopeId id, const Locus& locus)
    : Expr(id, locus), UnaryOp(rhs){}

  virtual std::string str() const noexcept{
    return std::string("@");
  };

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
};

/////////////////////////////////////////////////////////
class DerefOp : public ExprVar, public UnaryOp {
public:

  virtual ~DerefOp() = default;
  //TODO change op to own type
  DerefOp(PtrExpr& rhs, const ScopeId id, const Locus& locus)
    : ExprVar(id, locus), UnaryOp(rhs){}

  virtual std::string str() const noexcept{
    return std::string("*");
  };

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
};

}//end namespace AST
}//end namespace Compiler
