#pragma once
#include <memory>
#include "AST/Node.hpp"

namespace Compiler{
namespace AST{


/////////////////////////////////////////////////////////
class ClassDef : public Node, public NamedNode {
public:
  virtual ~ClassDef() = default;
  ClassDef(const std::string& name
    , std::vector<PtrVarDecl>& var_decl
    , std::vector<PtrFuncDef>& func_def
    , const ScopeId id
    , const Locus& locus)
  : Node(id, locus), NamedNode(name), var_decl_(std::move(var_decl))
  , func_def_(std::move(func_def)){}

  virtual void Accept(IRGenerator& v, const Node* successor);
  virtual void Accept(ASTVisitor& v);
  virtual std::string str() const noexcept { return "ClassDef: " + name_;}

  std::vector<PtrVarDecl>& GetVarDecl() noexcept{ return var_decl_;}
  const std::vector<PtrVarDecl>& GetVarDecl() const noexcept{ return var_decl_;}

private:
  std::vector<PtrVarDecl> var_decl_;
  std::vector<PtrFuncDef> func_def_;

public:
  using iterator       = std::vector<PtrFuncDef>::iterator;
  using const_iterator = std::vector<PtrFuncDef>::const_iterator;
  iterator begin() { return func_def_.begin(); }
  iterator end()   { return func_def_.end(); }
  const_iterator begin()  const { return func_def_.begin(); }
  const_iterator end()    const { return func_def_.end(); }
  const_iterator cbegin() const { return func_def_.cbegin(); }
  const_iterator cend()   const { return func_def_.cend(); }
};

/////////////////////////////////////////////////////////
// This is mean to te the Rhs of the dot operator
class VarName : public Node, public NamedNode{
public:
  virtual ~VarName() = default;
  VarName(const std::string& name, const ScopeId scope_id , const Locus& locus)
    : Node(scope_id, locus), NamedNode(name){}


  std::string str() const noexcept{return name_;}
  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);
};


/////////////////////////////////////////////////////////
class DotOp : public ExprVar{
public:

  virtual ~DotOp() = default;
  //TODO change op to own type
  DotOp(PtrExprVar& lhs, PtrVarName& rhs, const ScopeId scope_id
  , const Locus& locus)
    : ExprVar(scope_id, locus), lhs_(std::move(lhs)), rhs_(std::move(rhs)){}

  virtual std::string str() const noexcept{
    return lhs_->str() + "." + rhs_->str();
  };

  virtual void Accept(ASTVisitor& v);
  virtual void Accept(IRGenerator& v, const Node* successor);

  ExprVar& Lhs() const noexcept {return *lhs_;}
  VarName& Rhs() const noexcept {return *rhs_;}
private:
  PtrExprVar lhs_;
  PtrVarName rhs_;
};

}//end namespace AST
}//end namespace Compiler
