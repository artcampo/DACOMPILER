#include "Node.hpp"
#include "ASTVisitor.hpp"

void Block::Accept              (ASTVisitor& v){ v.Visit(*this); }
void ExpressionStatement::Accept(ASTVisitor& v){ v.Visit(*this); }
void Literal::Accept            (ASTVisitor& v){ v.Visit(*this); }
void BinaryOp::Accept           (ASTVisitor& v){ v.Visit(*this); }
