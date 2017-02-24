#pragma once
#include <memory>

namespace Compiler{
namespace AST{

class Node;
class Expr;
class DeclStmt;
class VarDeclList;
class VarDecl;
class AssignStmt;


/////////////////////////////////////////////////////////
class IfStmt : public Statement {
public:
  IfStmt(std::unique_ptr<Expr>& condition, std::unique_ptr<Block>& block1, std::unique_ptr<Block>& block2
        ,const ScopeId id, const Locus& locus)
   : Statement(id, locus), condition_(std::move(condition))
   , block1_(std::move(block1)), block2_(std::move(block2)){}


   /*
  IfStmt(std::unique_ptr<Expr>& condition, std::unique_ptr<Block>& block1, ScopeId id
    , const Locus& locus)
  : IfStmt(condition, block1, std::make_unique<Block>(nullptr), id, locus){}
*/
  IfStmt(std::unique_ptr<Expr>& condition, std::unique_ptr<Block>& block1, ScopeId id
    , const Locus& locus)
  : Statement(id, locus), condition_(std::move(condition))
   , block1_(std::move(block1)), block2_(nullptr){}

  Expr&  GetCond() const noexcept{ return *condition_;};
  Block& GetThen() const noexcept{ return *block1_;};
  Block& GetElse() const noexcept{ return *block2_;};
  const bool HasElse()const noexcept{ return block2_ != nullptr;};
  virtual std::string str() const;

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  std::unique_ptr<Expr> condition_;
  std::unique_ptr<Block>  block1_;
  std::unique_ptr<Block>  block2_;
};

/////////////////////////////////////////////////////////
class AssignStmt : public Statement {
public:
  AssignStmt(std::unique_ptr<Expr>& lhs, std::unique_ptr<Expr>& rhs, const ScopeId id
    , const Locus& locus)
    : Statement(id, locus), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

  Expr& Lhs() const noexcept{return *lhs_;}
  Expr& Rhs() const noexcept{return *rhs_;}

  virtual std::string str() const{
    return lhs_->str() + "=" + rhs_->str();
  };

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  std::unique_ptr<Expr> lhs_;
  std::unique_ptr<Expr> rhs_;
};

/////////////////////////////////////////////////////////
class DeclStmt : public Statement {
public:
  DeclStmt(std::unique_ptr<VarDeclList>& decl_list, const ScopeId id, const Locus& locus)
    : Statement(id, locus), decl_list_(std::move(decl_list)) {}

  VarDeclList& GetVarDeclList() const noexcept{return *decl_list_;}

  virtual std::string str() const;

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  std::unique_ptr<VarDeclList> decl_list_;
};

/////////////////////////////////////////////////////////
class WhileStmt : public Statement {
public:
  WhileStmt(std::unique_ptr<Expr>& condition, std::unique_ptr<Block>& body
        ,const ScopeId id, const Locus& locus)
   : Statement(id, locus), condition_(std::move(condition))
   , body_(std::move(body)){}

  Expr&  GetCond() const noexcept{ return *condition_;};
  Block& GetBody() const noexcept{ return *body_;};


  virtual std::string str() const;

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  std::unique_ptr<Expr>   condition_;
  std::unique_ptr<Block>  body_;
};

}//end namespace AST
}//end namespace Compiler
