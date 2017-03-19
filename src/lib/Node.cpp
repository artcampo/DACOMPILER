#include "AST/Node.hpp"
#include "AST/ASTVisitor.hpp"
#include "IR/IRGenerator.hpp"
#include "IRDefinition.hpp"
#include <cstddef>

namespace Compiler{
namespace AST{

void ProgBody::Accept    (ASTVisitor& v){ v.Visit(*this); }
void ProgInit::Accept    (ASTVisitor& v){ v.Visit(*this); }
void ProgEnd::Accept     (ASTVisitor& v){ v.Visit(*this); }
void FuncDef::Accept     (ASTVisitor& v){ v.Visit(*this); }
void ClassDef::Accept    (ASTVisitor& v){ v.Visit(*this); }


void Block::Accept       (ASTVisitor& v){ v.Visit(*this); }
void IfStmt::Accept      (ASTVisitor& v){ v.Visit(*this); }
void WhileStmt::Accept   (ASTVisitor& v){ v.Visit(*this); }
void DeclStmt::Accept    (ASTVisitor& v){ v.Visit(*this); }
void AssignStmt::Accept  (ASTVisitor& v){ v.Visit(*this); }
void Literal::Accept     (ASTVisitor& v){ v.Visit(*this); }
void VarDeclList::Accept (ASTVisitor& v){ v.Visit(*this); }
void VarDecl::Accept     (ASTVisitor& v){ v.Visit(*this); }
void Var::Accept         (ASTVisitor& v){ v.Visit(*this); }
void BinaryOp::Accept    (ASTVisitor& v){ v.Visit(*this); }
void RefOp::Accept       (ASTVisitor& v){ v.Visit(*this); }
void DerefOp::Accept     (ASTVisitor& v){ v.Visit(*this); }

void FuncCall::Accept    (ASTVisitor& v){ v.Visit(*this); }
void FuncRet::Accept     (ASTVisitor& v){ v.Visit(*this); }
void ReturnStmt::Accept  (ASTVisitor& v){ v.Visit(*this); }
void VarName::Accept     (ASTVisitor& v){ v.Visit(*this); }
void DotOp::Accept       (ASTVisitor& v){ v.Visit(*this); }


void ProgBody::Accept    (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void ProgInit::Accept    (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void ProgEnd::Accept     (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void FuncDef::Accept     (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void ClassDef::Accept    (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }

void Block::Accept       (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void IfStmt::Accept      (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void WhileStmt::Accept   (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void AssignStmt::Accept  (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void DeclStmt::Accept    (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void Literal::Accept     (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void VarDeclList::Accept (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void VarDecl::Accept     (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void Var::Accept         (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void BinaryOp::Accept    (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void RefOp::Accept       (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void DerefOp::Accept     (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void FuncCall::Accept    (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void FuncRet::Accept     (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void ReturnStmt::Accept  (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void VarName::Accept     (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }
void DotOp::Accept       (IRGenerator& v, const Node* successor){ return v.Visit(*this, successor); }


std::string BinaryOp::OpString() const noexcept{
  using namespace IRDefinition;
  using namespace SubtypesArithmetic;
  if (op == IR_ADD ) return " + ";
  if (op == IR_SUB ) return " - ";
  if (op == IR_MUL ) return " * ";
  if (op == IR_DIV ) return " / ";
}

std::string Block::str() const{
  std::string s("Block {");
  for(const auto& stmt : statements_)
    s += (stmt->str() +" ");
  s += "}";
  return s;
};

std::string VarDeclList::str() const{
  std::string s("VarDecl: ");
  for(const auto& d : list_)
    s += (d->str() + " ");
  return s;
};

std::string IfStmt::str() const{
  return "If";
};

std::string DeclStmt::str() const{
  return decl_list_->str();
};

std::string WhileStmt::str() const{
  std::string s("While (");
  s += GetCond().str();
  s +=") {";
  s += GetBody().str();
  s += "}";
  return s;
};



}//end namespace AST
}//end namespace Compiler
