#pragma once
// #include "ASTVisitor.hpp"
#include <iostream>
#include <vector>
#include <stdint.h>
#include <memory>
#include "Types.hpp"
#include "ScopeId.hpp"
#include "Locus.hpp"

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
  Node(const ScopeId id, const Locus& locus) : scope_id_(id), locus_(locus){}
  virtual ~Node() {}

  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Node";};
  virtual std::string str() const = 0;

  ScopeId GetScopeId() const noexcept{return scope_id_;};
private:
  ScopeId scope_id_;
  const Locus locus_;

};

class Expr : public Node{
public:
  Expr(const ScopeId id, const Locus& locus) : Node(id, locus){};
  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Expr";};
  virtual std::string str() const = 0;
};

/////////////////////////////////////////////////////////
class Statement  : public Node{
public:
  Statement(const ScopeId id, const Locus& locus) : Node(id, locus){};
  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Statement";};
  virtual std::string str() const = 0;
};

/////////////////////////////////////////////////////////
class Block : public Node {
public:
    Block(const ScopeId id, const Locus& locus) : Node(id, locus){}

    void AddStatement(Statement* const s){ statements.push_back(s);}

    Statement* FirstStatement(){return statements[0];}
    Statement* const FirstStatement() const{return statements[0];}

    void Accept(ASTVisitor& v);
    virtual std::string str() const{ return std::string("string not implemented");};

    std::vector<Statement*> statements;
};



/////////////////////////////////////////////////////////
class VarDeclList : public Node{
public:

  VarDeclList(const std::vector<VarDecl*>& list, const ScopeId id
            , const Locus& locus)
    : Node(id, locus), list_(list) {}
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

  VarDecl(const std::string& name, const TypeId& typeId, const ScopeId id
    , const Locus& locus)
    : Node(id, locus), name_(name), typeId_(typeId){}
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


}//end namespace AST
}//end namespace Compiler

#include "NodeExpr.hpp"
#include "NodeStmt.hpp"
