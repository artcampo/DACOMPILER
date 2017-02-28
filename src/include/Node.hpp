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

using NodeValue = uint32_t;
using OpType    = uint32_t; //TODO: USE THESE!!

namespace AST{

class Node;

class ASTVisitor;
class IRGenerator;

//subtypes of node, main components
class ProgBody;
class ProgInit;
class ProgEnd;
class Block;
class FuncDecl;

//subtypes of Statement
class Statement;
class IfStmt;
class WhileStmt;
class DeclStmt;
class AssignStmt;

//subtypes of node
class Expr;
class VarDeclList;
class VarDecl;

//subtypes of expr
class Literal;
class BinaryOp;
class Var;
class UnaryOp;
class RefOp;
class DerefOp;

namespace Ptrs{

using PtrProgBody   = std::unique_ptr<ProgBody>;
using PtrProgInit   = std::unique_ptr<ProgInit>;
using PtrProgEnd    = std::unique_ptr<ProgEnd>;
using PtrBlock      = std::unique_ptr<Block>;
using PtrFuncDecl   = std::unique_ptr<FuncDecl>;


using PtrStatement  = std::unique_ptr<Statement>;
using PtrIfStmt     = std::unique_ptr<IfStmt>;
using PtrWhileStmt  = std::unique_ptr<WhileStmt>;
using PtrDeclStmt   = std::unique_ptr<DeclStmt>;
using PtrAssignStmt = std::unique_ptr<AssignStmt>;
using PtrExpr       = std::unique_ptr<Expr>;
using PtrVarDeclList= std::unique_ptr<VarDeclList>;
using PtrVarDecl    = std::unique_ptr<VarDecl>;
using PtrLiteral    = std::unique_ptr<Literal>;
using PtrBinaryOp   = std::unique_ptr<BinaryOp>;
using PtrVar        = std::unique_ptr<Var>;
using PtrUnaryOp    = std::unique_ptr<UnaryOp>;
using PtrRefOp      = std::unique_ptr<RefOp>;
using PtrDerefOp    = std::unique_ptr<DerefOp>;

}//end namespace Ptrs
using namespace Compiler::AST::Ptrs;

class Node {
public:
  Node(const ScopeId id, const Locus& locus) : scope_id_(id), locus_(locus){}
  virtual ~Node() = default;

  virtual void Accept(ASTVisitor& v) = 0;
  virtual void Accept(IRGenerator& v, const Node* successor) = 0;
  virtual std::string str() const = 0;

  ScopeId GetScopeId() const noexcept{return scope_id_;};
  Locus   GetLocus() const noexcept{return locus_;};
private:
  ScopeId scope_id_;
  const Locus locus_;

};

class Expr : public Node{
public:
  virtual ~Expr() = default;
  Expr(const ScopeId id, const Locus& locus) : Node(id, locus){};
  virtual void Accept(ASTVisitor& v) = 0;
  virtual void Accept(IRGenerator& v, const Node* successor) = 0;
  virtual std::string str() const = 0;
};

/////////////////////////////////////////////////////////
class Statement  : public Node{
public:
  virtual ~Statement() = default;
  Statement(const ScopeId id, const Locus& locus) : Node(id, locus){};
  virtual void Accept(ASTVisitor& v) = 0;
  virtual void Accept(IRGenerator& v, const Node* successor) = 0;
  virtual std::string str() const = 0;
};

/////////////////////////////////////////////////////////
class Block : public Node {
public:
  virtual ~Block() = default;
  Block(const ScopeId id, const Locus& locus) : Node(id, locus){}

  void AddStatement(PtrStatement& s){ statements_.push_back(std::move(s));}


  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const;

  std::vector<PtrStatement> statements_;
};

/////////////////////////////////////////////////////////
class FuncDecl : public Node {
public:
  virtual ~FuncDecl() = default;
  FuncDecl(const ScopeId id, const Locus& locus
    , std::string& name
    , PtrBlock& block)
  : Node(id, locus), block_(std::move(block)), name_(name){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return std::string("FuncDecl: ") + name_;}

  Block&    GetBody() const noexcept{ return *block_;}
private:
//   PtrArg
  PtrBlock      block_;
  std::string   name_;
};

/////////////////////////////////////////////////////////
class ProgBody : public Node {
public:
  virtual ~ProgBody() = default;
  ProgBody(const ScopeId id, const Locus& locus
    , PtrProgInit& pinit
    , PtrProgEnd& pend
    , PtrFuncDecl& main)
  : Node(id, locus), pinit_(std::move(pinit)), pend_(std::move(pend))
  , main_(std::move(main)){}


  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const{ return std::string("ProgBody");};

  ProgInit& GetProgInit() const noexcept{ return *pinit_;}
  ProgEnd&  GetProgEnd()  const noexcept{ return *pend_;}
  FuncDecl& GetMainFunc()    const noexcept{ return *main_;}
private:
  PtrProgInit  pinit_;
  PtrProgEnd   pend_;
  PtrFuncDecl  main_;
};

/////////////////////////////////////////////////////////
class ProgInit : public Node {
public:
  virtual ~ProgInit() = default;
    ProgInit(const ScopeId id, const Locus& locus) : Node(id, locus){}


    virtual void Accept(IRGenerator& v, const Node* successor);
    virtual void Accept(ASTVisitor& v);
    virtual std::string str() const{ return std::string("ProgInit");};
};

/////////////////////////////////////////////////////////
class ProgEnd : public Node {
public:
  virtual ~ProgEnd() = default;
    ProgEnd(const ScopeId id, const Locus& locus) : Node(id, locus){}

    virtual void Accept(IRGenerator& v, const Node* successor);
    virtual void Accept(ASTVisitor& v);
    virtual std::string str() const{ return std::string("ProgEnd");};
};

/////////////////////////////////////////////////////////
class VarDeclList : public Node{
public:

  virtual ~VarDeclList() = default;
  VarDeclList(std::vector<PtrVarDecl>& list, const ScopeId id
            , const Locus& locus)
    : Node(id, locus)
    {for (const auto& it : list) list_.push_back(std::make_unique<VarDecl>(*it));}

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);

  std::vector<PtrVarDecl>& GetVarDeclVector() noexcept{return list_;};
  const std::vector<PtrVarDecl>& GetVarDeclVector() const noexcept{return list_;};
  virtual std::string str() const;
private:
  std::vector<PtrVarDecl> list_;
};

/////////////////////////////////////////////////////////
class VarDecl : public Node{
public:
  virtual ~VarDecl() = default;
  VarDecl(const std::string& name, const Type& type, const ScopeId id
    , const Locus& locus)
    : Node(id, locus), name_(name), type_(type){}
  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);

  std::string str() const noexcept{
    std::string s;
    s += type_.str();
    s += " ";
    s += name_;
    return s;
  }

private:
  const std::string name_;
  const Type& type_;
};


}//end namespace AST

}//end namespace Compiler

#include "NodeExpr.hpp"
#include "NodeStmt.hpp"
