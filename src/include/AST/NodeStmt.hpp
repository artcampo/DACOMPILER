#pragma once
#include <memory>
#include "AST/Node.hpp"

namespace Compiler{
namespace AST{

class Node;
class Expr;
class DeclStmt;
class VarDeclList;
class VarDecl;
class AssignStmt;
class FuncDef;


/////////////////////////////////////////////////////////
class IfStmt : public Statement {
public:
  virtual ~IfStmt() = default;
  IfStmt(PtrExpr& condition, PtrBlock& block1, PtrBlock& block2
        ,const ScopeId id, const Locus& locus)
   : Statement(id, locus), condition_(std::move(condition))
   , block1_(std::move(block1)), block2_(std::move(block2)){}


   /*
  IfStmt(PtrExpr& condition, PtrBlock& block1, ScopeId id
    , const Locus& locus)
  : IfStmt(condition, block1, std::make_unique<Block>(nullptr), id, locus){}
*/
  IfStmt(PtrExpr& condition, PtrBlock& block1, ScopeId id
    , const Locus& locus)
  : Statement(id, locus), condition_(std::move(condition))
   , block1_(std::move(block1)), block2_(nullptr){}

  Expr&  GetCond() const noexcept{ return *condition_;};
  Block& GetThen() const noexcept{ return *block1_;};
  Block& GetElse() const noexcept{ return *block2_;};
  const bool HasElse()const noexcept{ return block2_ != nullptr;};
  virtual std::string str() const;

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
private:
  PtrExpr condition_;
  PtrBlock  block1_;
  PtrBlock  block2_;
};

/////////////////////////////////////////////////////////
class AssignStmt : public Statement {
public:
  virtual ~AssignStmt() = default;
  AssignStmt(PtrExpr& lhs, PtrExpr& rhs, const ScopeId id
    , const Locus& locus)
    : Statement(id, locus), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

  Expr& Lhs() const noexcept{return *lhs_;}
  Expr& Rhs() const noexcept{return *rhs_;}

  virtual std::string str() const{
    return lhs_->str() + "=" + rhs_->str();
  };

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
private:
  PtrExpr lhs_;
  PtrExpr rhs_;
};

/////////////////////////////////////////////////////////
class DeclStmt : public Statement {
public:
  virtual ~DeclStmt() = default;
  DeclStmt(PtrVarDeclList& decl_list, const ScopeId id, const Locus& locus)
    : Statement(id, locus), decl_list_(std::move(decl_list)) {}


//   VarDeclList& GetVarDeclList() noexcept{return *decl_list_;}
//   const VarDeclList& GetVarDeclList() const noexcept{return *decl_list_;}
  VarDeclList& GetVarDeclList() const noexcept{return *decl_list_;}

  virtual std::string str() const;

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
private:
  PtrVarDeclList decl_list_;
};

/////////////////////////////////////////////////////////
class WhileStmt : public Statement {
public:
  virtual ~WhileStmt() = default;
  WhileStmt(PtrExpr& condition, PtrBlock& body
        ,const ScopeId id, const Locus& locus)
   : Statement(id, locus), condition_(std::move(condition))
   , body_(std::move(body)){}

  Expr&  GetCond() const noexcept{ return *condition_;};
  Block& GetBody() const noexcept{ return *body_;};


  virtual std::string str() const;

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
private:
  PtrExpr   condition_;
  PtrBlock  body_;
};



/////////////////////////////////////////////////////////
class ReturnStmt : public Statement {
public:
  virtual ~ReturnStmt() = default;
  ReturnStmt(PtrExpr& ret_expr, FuncDecl& func_decl, const ScopeId id, const Locus& locus)
    : Statement(id, locus), ret_expr_(std::move(ret_expr)), func_decl_(func_decl){}

  Expr& RetExpr() const noexcept{return *ret_expr_;}
  FuncDecl& GetFuncDecl() const noexcept{return func_decl_;}

  virtual std::string str() const{
    return "Return (" + ret_expr_->str() + ")";
  };

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
private:
  PtrExpr ret_expr_;
  FuncDecl& func_decl_;
};

}//end namespace AST
}//end namespace Compiler
