#include "Node.hpp"
#include "ASTVisitor.hpp"
#include "IRDefinition.hpp"

namespace Compiler{
namespace AST{

void Block::Accept              (ASTVisitor& v){ v.Visit(*this); }
void ExpressionStatement::Accept(ASTVisitor& v){ v.Visit(*this); }
void StmtIf::Accept             (ASTVisitor& v){ v.Visit(*this); }
void Literal::Accept            (ASTVisitor& v){ v.Visit(*this); }
void BinaryOp::Accept           (ASTVisitor& v){ v.Visit(*this); }
void DeclStmt::Accept           (ASTVisitor& v){ v.Visit(*this); }
void VarDeclList::Accept        (ASTVisitor& v){ v.Visit(*this); }
void VarDecl::Accept            (ASTVisitor& v){ v.Visit(*this); }


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
