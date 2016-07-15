#include "Node.h"
#include "ASTVisitor.hpp"

void Block::Accept              (ASTVisitor& v){  std::cout << "Accept on Block\n";v.Visit(*this);}
void ExpressionStatement::Accept(ASTVisitor& v){ v.Visit(*this); std::cout << "Accept on ExtStmt\n";v.Visit(*this);}
void Literal::Accept            (ASTVisitor& v){  std::cout << "Accept on Liter\n";v.Visit(*this);}
void BinaryOp::Accept           (ASTVisitor& v){ std::cout << "Accept on BinOp\n";v.Visit(*this);}
