#pragma once
// #include "ASTVisitor.hpp"
#include <iostream>
#include <vector>
#include <stdint.h>
#include <memory>
#include "Types.hpp"
#include "ScopeId.hpp"


namespace Compiler{
namespace AST{

class ASTVisitor;

class Node;
class Expr;
class DeclStmt;
class VarDeclList;
class VarDecl;
class AssignStmt;

class Node {
public:
  Node(const ScopeId id) : scope_id_(id){}
  virtual ~Node() {}

  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Node";};
  virtual std::string str() const = 0;

  ScopeId GetScopeId() const noexcept{return scope_id_;};
private:
  ScopeId scope_id_;

};

class Expr : public Node{
public:
  Expr(const ScopeId id) : Node(id){};
  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Expr";};
  virtual std::string str() const = 0;
};

/////////////////////////////////////////////////////////
class Statement  : public Node{
public:
  Statement(const ScopeId id) : Node(id){};
  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Statement";};
  virtual std::string str() const = 0;
};

/////////////////////////////////////////////////////////
class Block : public Node {
public:
    std::vector<Statement*> statements;
    Block(const ScopeId id) : Node(id){}

    void AddStatement(Statement* const s){ statements.push_back(s);}

    Statement* FirstStatement(){return statements[0];}
    Statement* const FirstStatement() const{return statements[0];}

    void Accept(ASTVisitor& v);
    virtual std::string str() const{ return std::string("string not implemented");};
};

/////////////////////////////////////////////////////////
class IfStmt : public Statement {
public:
  IfStmt(Expr* const condition, Block* const block1, Block* const block2
        ,const ScopeId id)
   : Statement(id), condition_(condition), block1_(block1), block2_(block2){}

  IfStmt(Expr* const condition, Block* const block1, const ScopeId id)
  : Statement(id), condition_(condition), block1_(block1), block2_(nullptr){}

  void Accept(ASTVisitor& v);

  Expr* GetCond() const noexcept{ return condition_;};
  Block* GetThen() const noexcept{ return block1_;};
  Block* GetElse() const noexcept{ return block2_;};
  const bool HasElse()const noexcept{ return block2_ != nullptr;};
  virtual std::string str() const{ return std::string("string not implemented");};

private:
  Expr* condition_;
  Block*  block1_;
  Block*  block2_;
};

/////////////////////////////////////////////////////////
class AssignStmt : public Statement {
public:
  AssignStmt(Expr* const lhs, Expr* const rhs, const ScopeId id)
    : Statement(id), lhs_(lhs), rhs_(rhs) {}
  void Accept(ASTVisitor& v);

  Expr* const Lhs() const noexcept{return lhs_.get();}
  Expr* const Rhs() const noexcept{return rhs_.get();}

  virtual std::string str() const{
    return lhs_->str() + "=" + rhs_->str();
  };
private:
  std::unique_ptr<Expr> lhs_;
  std::unique_ptr<Expr> rhs_;
};

/////////////////////////////////////////////////////////
class DeclStmt : public Statement {
public:
  DeclStmt(VarDeclList* const decl_list, const ScopeId id)
    : Statement(id), decl_list_(decl_list) {}
  void Accept(ASTVisitor& v);
  VarDeclList* const GetVarDeclList() const noexcept{return decl_list_;}

  virtual std::string str() const{ return std::string("string not implemented");};
private:
  VarDeclList* decl_list_;
};


/////////////////////////////////////////////////////////
class VarDeclList : public Node{
public:

  VarDeclList(const std::vector<VarDecl*>& list, const ScopeId id)
    : Node(id), list_(list) {}
  virtual void Accept(ASTVisitor& v);

  std::vector<VarDecl*>& GetVarDeclVector() noexcept{return list_;};
  const std::vector<VarDecl*>& GetVarDeclVector() const noexcept{return list_;};
  virtual std::string str() const{ return std::string("string not implemented");};
private:
  std::vector<VarDecl*> list_;
};

/////////////////////////////////////////////////////////
class VarDecl : public Node{
public:

  VarDecl(const std::string& name, const TypeId& typeId, const ScopeId id)
    : Node(id), name_(name), typeId_(typeId){}
  virtual void Accept(ASTVisitor& v);

  std::string str() const noexcept{
    std::string s;
    s += typeId_.str();
    s += " ";
    s += name_;
    return s;
  }

private:
  const std::string name_;
  const TypeId typeId_;
};


/////////////////////////////////////////////////////////
class Literal : public Expr {
public:
  Literal(const uint32_t &value, const TypeId& t, const ScopeId id)
    : Expr(id), value_(value), t_(t){}

  TypeId GetTypeId()const noexcept{return t_;}
  uint32_t Value() const noexcept{ return value_;};

  void Accept(ASTVisitor& v);
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
  BinaryOp(Expr* const lhs, const int op, Expr* const rhs, const ScopeId id)
    : Expr(id), lhs_(lhs), rhs_(rhs), op(op){}

  void Accept(ASTVisitor& v);

  Expr* Lhs() const noexcept{return lhs_;}
  Expr* Rhs() const noexcept{return rhs_;}

  //TODO: merge these
  std::string OpString() const noexcept;
  std::string str() const noexcept{return OpString();}
private:
  Expr* lhs_;
  Expr* rhs_;
};


/////////////////////////////////////////////////////////
class Var : public Expr{
public:

  Var(const std::string& name, const TypeId& t, const ScopeId id)
    : Expr(id), name_(name),t_(t){}
  virtual void Accept(ASTVisitor& v);

  TypeId GetTypeId()const noexcept{return t_;}
  std::string str() const noexcept{return name_;}

private:
  const std::string name_;
  TypeId  t_;
};

}//end namespace AST
}//end namespace Compiler
