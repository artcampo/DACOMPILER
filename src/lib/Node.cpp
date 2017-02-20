#include "Node.hpp"
#include "ASTVisitor.hpp"
#include "ASTVisitorCodeGenerator.hpp"
#include "IRDefinition.hpp"
#include <cstddef>

namespace Compiler{
namespace AST{

void Prog::Accept       (ASTVisitor& v){ v.Visit(*this); }
void ProgInit::Accept       (ASTVisitor& v){ v.Visit(*this); }
void ProgEnd::Accept       (ASTVisitor& v){ v.Visit(*this); }
void Block::Accept       (ASTVisitor& v){ v.Visit(*this); }
void IfStmt::Accept      (ASTVisitor& v){ v.Visit(*this); }
void Literal::Accept     (ASTVisitor& v){ v.Visit(*this); }
void BinaryOp::Accept    (ASTVisitor& v){ v.Visit(*this); }
void DeclStmt::Accept    (ASTVisitor& v){ v.Visit(*this); }
void VarDeclList::Accept (ASTVisitor& v){ v.Visit(*this); }
void VarDecl::Accept     (ASTVisitor& v){ v.Visit(*this); }
void AssignStmt::Accept  (ASTVisitor& v){ v.Visit(*this); }
void Var::Accept         (ASTVisitor& v){ v.Visit(*this); }


void Prog::Accept       (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void ProgInit::Accept       (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void ProgEnd::Accept       (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void Block::Accept       (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void IfStmt::Accept      (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void Literal::Accept     (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void BinaryOp::Accept    (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void DeclStmt::Accept    (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void VarDeclList::Accept (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void VarDecl::Accept     (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void AssignStmt::Accept  (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }
void Var::Accept         (CodeGen& v, const Statement* successor){ return v.Visit(*this, successor); }

std::string BinaryOp::OpString() const noexcept{
  using namespace IRDefinition;
  using namespace SubtypesArithmetic;
  if (op == IR_ADD ) return std::string(" + ");
  if (op == IR_SUB ) return std::string(" - ");
  if (op == IR_MUL ) return std::string(" * ");
  if (op == IR_DIV ) return std::string(" / ");
}

}//end namespace AST
}//end namespace Compiler
