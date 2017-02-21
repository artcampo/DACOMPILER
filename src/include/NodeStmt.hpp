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
  IfStmt(Expr* const condition, Block* const block1, Block* const block2
        ,const ScopeId id, const Locus& locus)
   : Statement(id, locus), condition_(condition), block1_(block1), block2_(block2){}

  IfStmt(Expr* const condition, Block* const block1, const ScopeId id
    , const Locus& locus)
  : IfStmt(condition, block1, nullptr, id, locus){}
  //Statement(id), condition_(condition), block1_(block1), block2_(nullptr){}

  Expr*  GetCond() const noexcept{ return condition_;};
  Block* GetThen() const noexcept{ return block1_;};
  Block* GetElse() const noexcept{ return block2_;};
  const bool HasElse()const noexcept{ return block2_ != nullptr;};
  virtual std::string str() const;

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  Expr* condition_;
  Block*  block1_;
  Block*  block2_;
};

/////////////////////////////////////////////////////////
class AssignStmt : public Statement {
public:
  AssignStmt(Expr* const lhs, Expr* const rhs, const ScopeId id
    , const Locus& locus)
    : Statement(id, locus), lhs_(lhs), rhs_(rhs) {}

  Expr* const Lhs() const noexcept{return lhs_.get();}
  Expr* const Rhs() const noexcept{return rhs_.get();}

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
  DeclStmt(VarDeclList* const decl_list, const ScopeId id, const Locus& locus)
    : Statement(id, locus), decl_list_(decl_list) {}

  VarDeclList* const GetVarDeclList() const noexcept{return decl_list_;}

  virtual std::string str() const;

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  VarDeclList* decl_list_;
};

/////////////////////////////////////////////////////////
class WhileStmt : public Statement {
public:
  WhileStmt(std::unique_ptr<Expr>& condition, std::unique_ptr<Block>& body
        ,const ScopeId id, const Locus& locus)
   : Statement(id, locus), condition_(std::move(condition))
   , body_(std::move(body)){}

  Expr*  GetCond() const noexcept{ return condition_.get();};
  Block* GetBody() const noexcept{ return body_.get();};


  virtual std::string str() const;

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);
private:
  std::unique_ptr<Expr>   condition_;
  std::unique_ptr<Block>  body_;
};

}//end namespace AST
}//end namespace Compiler