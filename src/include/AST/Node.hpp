#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include <memory>
#include <cstddef>
#include "Types.hpp"
#include "Scopes/ScopeId.hpp"
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
class FuncDef;
class FuncDecl;

//subtypes of Statement
class Statement;
class IfStmt;
class WhileStmt;
class DeclStmt;
class AssignStmt;
class ReturnStmt;

//subtypes of node
class Expr;
class ExprVar;
class VarDeclList;
class VarDecl;

//subtypes of expr
class Literal;
class BinaryOp;
class UnaryOp;
class RefOp;

//subtypes of ExprVar (can evaluate to lval, unlike Expr)
class Var;
class FuncRet;
class DerefOp;
class DotOp;

//Functions

class FuncCall;

//Class related nodes
class ClassDef;
class VarName;

namespace Ptrs{

using PtrProgBody   = std::unique_ptr<ProgBody>;
using PtrProgInit   = std::unique_ptr<ProgInit>;
using PtrProgEnd    = std::unique_ptr<ProgEnd>;
using PtrBlock      = std::unique_ptr<Block>;
using PtrFuncDef    = std::unique_ptr<FuncDef>;
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
using PtrFuncRet    = std::unique_ptr<FuncRet>;
using PtrFuncCall   = std::unique_ptr<FuncCall>;
using PtrReturnStmt = std::unique_ptr<ReturnStmt>;
using PtrClassDef   = std::unique_ptr<ClassDef>;
using PtrVarName    = std::unique_ptr<VarName>;
using PtrExprVar    = std::unique_ptr<ExprVar>;
using PtrDotOp      = std::unique_ptr<DotOp>;


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

struct NamedNode{
  NamedNode(const std::string& name) : name_(name){}
  const std::string&  Name() const noexcept{ return name_;}
protected:
  const std::string name_;
};

struct TypedNode{
  TypedNode(const Type& type) : type_(&type){}
  const Type& GetType()const noexcept{return *type_;}
  void SetType(const Type& type)noexcept{type_ = &type;}
protected:
  const Type*  type_;
};



class Expr : public Node{
public:
  virtual ~Expr() = default;
  Expr(const ScopeId id, const Locus& locus) : Node(id, locus){};
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
class ProgBody : public Node {
public:
  virtual ~ProgBody() = default;
  ProgBody(const ScopeId id, const Locus& locus
    , PtrProgInit& pinit
    , PtrProgEnd& pend
    , std::vector<PtrFuncDef>& functions
    , std::vector<PtrClassDef>& classes)
  : Node(id, locus), pinit_(std::move(pinit)), pend_(std::move(pend))
  , functions_(std::move(functions))
  , classes_(std::move(classes)){}


  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const{ return "ProgBody";};

  ProgInit& GetProgInit() const noexcept{ return *pinit_;}
  ProgEnd&  GetProgEnd()  const noexcept{ return *pend_;}

  std::vector<PtrClassDef>& GetClassDefs() noexcept{ return classes_;}
  const std::vector<PtrClassDef>& GetClassDefs() const noexcept{ return classes_;}
private:
  PtrProgInit               pinit_;
  PtrProgEnd                pend_;
  std::vector<PtrFuncDef>   functions_;
  std::vector<PtrClassDef>  classes_;
public:

  using iterator = std::vector<PtrFuncDef>::iterator;
  using const_iterator = std::vector<PtrFuncDef>::const_iterator;

  iterator begin() { return functions_.begin(); }
  iterator end()   { return functions_.end(); }
  const_iterator begin()  const { return functions_.begin(); }
  const_iterator end()    const { return functions_.end(); }
  const_iterator cbegin() const { return functions_.cbegin(); }
  const_iterator cend()   const { return functions_.cend(); }
};

/////////////////////////////////////////////////////////
class ProgInit : public Node {
public:
  virtual ~ProgInit() = default;
    ProgInit(const ScopeId id, const Locus& locus) : Node(id, locus){}


    virtual void Accept(IRGenerator& v, const Node* successor);
    virtual void Accept(ASTVisitor& v);
    virtual std::string str() const{ return "ProgInit";};
};

/////////////////////////////////////////////////////////
class ProgEnd : public Node {
public:
  virtual ~ProgEnd() = default;
    ProgEnd(const ScopeId id, const Locus& locus) : Node(id, locus){}

    virtual void Accept(IRGenerator& v, const Node* successor);
    virtual void Accept(ASTVisitor& v);
    virtual std::string str() const{ return "ProgEnd";};
};


}//end namespace AST
}//end namespace Compiler


