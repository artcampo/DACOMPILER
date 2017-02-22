#pragma once
#include <memory>
// #include "ASTVisitor.hpp"


namespace Compiler{
namespace AST{

class Node;
class Expr;
class DeclStmt;
class VarDeclList;
class VarDecl;
class AssignStmt;


/////////////////////////////////////////////////////////
class Literal : public Expr {
public:
  Literal(const uint32_t &value, const TypeId& t, const ScopeId id
    , const Locus& locus)
    : Expr(id, locus), value_(value), t_(t){}

  TypeId GetTypeId()const noexcept{return t_;}
  uint32_t Value() const noexcept{ return value_;};

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
  std::string str() const noexcept{return std::to_string(value_);}

private:
  TypeId  t_;
  uint32_t  value_;
};


/////////////////////////////////////////////////////////
class BinaryOp : public Expr {
public:
  int op;
  //TODO change op to own type
  BinaryOp(Expr* const lhs, const int op, Expr* const rhs, const ScopeId id
    , const Locus& locus)
    : Expr(id, locus), lhs_(lhs), rhs_(rhs), op(op){}

  Expr* Lhs() const noexcept{return lhs_;}
  Expr* Rhs() const noexcept{return rhs_;}

  //TODO: merge these
  std::string OpString() const noexcept;
  std::string str() const noexcept{return OpString();}

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  Expr* lhs_;
  Expr* rhs_;
};


/////////////////////////////////////////////////////////
class Var : public Expr{
public:

  Var(const std::string& name, const TypeId& t, const ScopeId id
    , const Locus& locus)
    : Expr(id, locus), name_(name),t_(t){}

  TypeId GetTypeId()const noexcept{return t_;}
  std::string str() const noexcept{return name_;}

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  const std::string name_;
  TypeId  t_;
};

/////////////////////////////////////////////////////////
class UnaryOp : public Expr {
public:

  //TODO change op to own type
  UnaryOp( Expr* const rhs, const ScopeId id
    , const Locus& locus)
    : Expr(id, locus), rhs_(rhs){}

  Expr* Rhs() const noexcept{return rhs_;}

  virtual std::string str() const noexcept = 0;

  virtual void Accept(ASTVisitor& v) = 0;
  virtual void Accept(CodeGen& v, const Node* successor) = 0;
private:
  Expr* rhs_;
};

/////////////////////////////////////////////////////////
class RefOp : public UnaryOp {
public:

  //TODO change op to own type
  RefOp( Expr* const rhs, const ScopeId id, const Locus& locus)
    : UnaryOp(rhs, id, locus){}

  virtual std::string str() const noexcept{
    return std::string("@");
  };

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
};

/////////////////////////////////////////////////////////
class DerefOp : public UnaryOp {
public:

  //TODO change op to own type
  DerefOp( Expr* const rhs, const ScopeId id, const Locus& locus)
    : UnaryOp(rhs, id, locus){}

  virtual std::string str() const noexcept{
    return std::string("@");
  };

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
};

}//end namespace AST
}//end namespace Compiler
