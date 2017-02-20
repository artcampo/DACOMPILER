#pragma once
// #include "ASTVisitor.hpp"
#include <iostream>
#include <vector>
#include <stdint.h>
#include <memory>
#include <cstddef>
#include "Types.hpp"
#include "ScopeId.hpp"
#include "Locus.hpp"

namespace Compiler{
namespace AST{

class Node;

class ASTVisitor;
class CodeGen;

class Expr;
class Statement;
class DeclStmt;
class VarDeclList;
class VarDecl;
class AssignStmt;
class ProgBody;
class ProgInit;
class ProgEnd;

class Node {
public:
  Node(const ScopeId id, const Locus& locus) : scope_id_(id), locus_(locus){}
  virtual ~Node() {}

  virtual void Accept(ASTVisitor& v) = 0;
  virtual void Accept(CodeGen& v, const Node* successor) = 0;
  virtual std::string str() const = 0;

  ScopeId GetScopeId() const noexcept{return scope_id_;};
  Locus   GetLocus() const noexcept{return locus_;};
private:
  ScopeId scope_id_;
  const Locus locus_;

};

class Expr : public Node{
public:
  Expr(const ScopeId id, const Locus& locus) : Node(id, locus){};
  virtual void Accept(ASTVisitor& v) = 0;
  virtual void Accept(CodeGen& v, const Node* successor) = 0;
  virtual std::string str() const = 0;
};

/////////////////////////////////////////////////////////
class Statement  : public Node{
public:
  Statement(const ScopeId id, const Locus& locus) : Node(id, locus){};
  virtual void Accept(ASTVisitor& v) = 0;
  virtual void Accept(CodeGen& v, const Node* successor) = 0;
  virtual std::string str() const = 0;
};

/////////////////////////////////////////////////////////
class Block : public Node {
public:
    Block(const ScopeId id, const Locus& locus) : Node(id, locus){}

    void AddStatement(Statement* const s){ statements.push_back(s);}

    Statement* FirstStatement(){return statements[0];}
    Statement* const FirstStatement() const{return statements[0];}

    virtual void Accept(CodeGen& v, const Node* successor);
    virtual void Accept(ASTVisitor& v);
    virtual std::string str() const;

    std::vector<Statement*> statements;
};

/////////////////////////////////////////////////////////
class ProgBody : public Node {
public:
  ProgBody(const ScopeId id, const Locus& locus
    , std::unique_ptr<AST::ProgInit>& pinit
    , std::unique_ptr<AST::ProgEnd>& pend
    , std::unique_ptr<AST::Block>& block)
  : Node(id, locus), pinit_(std::move(pinit)), pend_(std::move(pend))
  , block_(std::move(block)){}


  virtual void Accept(CodeGen& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const{ return std::string("ProgBody");};

//   ProgInit* GetProgInit() noexcept{ return pinit_.get();}
//   ProgEnd*  GetProgEnd()  noexcept{ return pend_.get();}
//   Block*    GetBlock()    noexcept{ return block_.get();}

  ProgInit* GetProgInit() const noexcept{ return pinit_.get();}
  ProgEnd*  GetProgEnd()  const noexcept{ return pend_.get();}
  Block*    GetBlock()    const noexcept{ return block_.get();}
private:
  std::unique_ptr<AST::ProgInit>  pinit_;
  std::unique_ptr<AST::ProgEnd>   pend_;
  std::unique_ptr<AST::Block>     block_;
};

/////////////////////////////////////////////////////////
class ProgInit : public Node {
public:
    ProgInit(const ScopeId id, const Locus& locus) : Node(id, locus){}


    virtual void Accept(CodeGen& v, const Node* successor);
    virtual void Accept(ASTVisitor& v);
    virtual std::string str() const{ return std::string("ProgInit");};
};

/////////////////////////////////////////////////////////
class ProgEnd : public Node {
public:
    ProgEnd(const ScopeId id, const Locus& locus) : Node(id, locus){}

    virtual void Accept(CodeGen& v, const Node* successor);
    virtual void Accept(ASTVisitor& v);
    virtual std::string str() const{ return std::string("ProgEnd");};
};

/////////////////////////////////////////////////////////
class VarDeclList : public Node{
public:

  VarDeclList(const std::vector<VarDecl*>& list, const ScopeId id
            , const Locus& locus)
    : Node(id, locus), list_(list) {}
  virtual void Accept(ASTVisitor& v);
  virtual void Accept(CodeGen& v, const Node* successor);

  std::vector<VarDecl*>& GetVarDeclVector() noexcept{return list_;};
  const std::vector<VarDecl*>& GetVarDeclVector() const noexcept{return list_;};
  virtual std::string str() const;
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
  virtual void Accept(CodeGen& v, const Node* successor);

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
