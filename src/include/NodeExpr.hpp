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
  virtual ~Literal() = default;
  Literal(const uint32_t &value, const Type& type, const ScopeId id
    , const Locus& locus)
    : Expr(id, locus), value_(value), type_(type){}

  const Type& GetType()const noexcept{return type_;}
  uint32_t Value() const noexcept{ return value_;};

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
  std::string str() const noexcept{return std::to_string(value_);}

private:
  const Type&  type_;
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
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  PtrExpr lhs_;
  PtrExpr rhs_;
};


/////////////////////////////////////////////////////////
class Var : public Expr{
public:
  virtual ~Var() = default;
  Var(const std::string& name, const Type& type, const ScopeId id
    , const Locus& locus)
    : Expr(id, locus), name_(name),type_(type){}

  const Type& GetType()const noexcept{return type_;}
  std::string str() const noexcept{return name_;}

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  const std::string name_;
  const Type&  type_;
};

/////////////////////////////////////////////////////////
class UnaryOp : public Expr {
public:

  virtual ~UnaryOp() = default;
  //TODO change op to own type
  UnaryOp(PtrExpr& rhs, const ScopeId id
    , const Locus& locus)
    : Expr(id, locus), rhs_(std::move(rhs)){}

  Expr& Rhs() const noexcept{return *rhs_;}

  virtual std::string str() const noexcept = 0;

  virtual void Accept(ASTVisitor& v) = 0;
  virtual void Accept(CodeGen& v, const Node* successor) = 0;
private:
  PtrExpr rhs_;
};

/////////////////////////////////////////////////////////
class RefOp : public UnaryOp {
public:

  virtual ~RefOp() = default;
  //TODO change op to own type
  RefOp(PtrExpr& rhs, const ScopeId id, const Locus& locus)
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

  virtual ~DerefOp() = default;
  //TODO change op to own type
  DerefOp(PtrExpr& rhs, const ScopeId id, const Locus& locus)
    : UnaryOp(rhs, id, locus){}

  virtual std::string str() const noexcept{
    return std::string("*");
  };

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
};

}//end namespace AST
}//end namespace Compiler
