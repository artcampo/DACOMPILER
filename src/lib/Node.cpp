#include "Node.hpp"
#include "ASTVisitor.hpp"
#include "ASTVisitorCodeGenerator.hpp"
#include "IRDefinition.hpp"
#include <cstddef>

namespace Compiler{
namespace AST{

void ProgBody::Accept    (ASTVisitor& v){ v.Visit(*this); }
void ProgInit::Accept    (ASTVisitor& v){ v.Visit(*this); }
void ProgEnd::Accept     (ASTVisitor& v){ v.Visit(*this); }
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
// void UnaryOp::Accept     (ASTVisitor& v){ v.Visit(*this); }


void ProgBody::Accept    (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void ProgInit::Accept    (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void ProgEnd::Accept     (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void Block::Accept       (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void IfStmt::Accept      (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void WhileStmt::Accept   (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void AssignStmt::Accept  (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void DeclStmt::Accept    (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void Literal::Accept     (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void VarDeclList::Accept (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void VarDecl::Accept     (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void Var::Accept         (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void BinaryOp::Accept    (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void RefOp::Accept       (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
void DerefOp::Accept     (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }
// void UnaryOp::Accept     (CodeGen& v, const Node* successor){ return v.Visit(*this, successor); }

std::string BinaryOp::OpString() const noexcept{
  using namespace IRDefinition;
  using namespace SubtypesArithmetic;
  if (op == IR_ADD ) return std::string(" + ");
  if (op == IR_SUB ) return std::string(" - ");
  if (op == IR_MUL ) return std::string(" * ");
  if (op == IR_DIV ) return std::string(" / ");
}

std::string Block::str() const{
  std::string s("Block {");
  for(const auto& stmt : statements_)
    s += (stmt->str() +std::string(" "));
  s += std::string("}");
  return s;
};

std::string VarDeclList::str() const{
  std::string s("VarDecl: ");
  for(const auto& d : list_)
    s += (d->str() +std::string(" "));
  return s;
};

std::string IfStmt::str() const{
  return std::string("If");
};

std::string DeclStmt::str() const{
  return decl_list_->str();
};

std::string WhileStmt::str() const{
  std::string s("While (");
  s += GetCond().str();
  s += std::string(") {");
  s += GetBody().str();
  s += std::string("}");
  return s;
};



}//end namespace AST
}//end namespace Compiler
