#pragma once
#include "ASTVisitor.hpp"
#include <iostream>
#include <vector>
#include <stdint.h>


class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;


// namespace AST_Nodes{

class Node {
public:
    virtual ~Node() {}
    
    virtual void Accept(ASTVisitor& v) = 0;
    
};

class Expression : public Node{
  virtual void Accept(ASTVisitor& v) = 0;
};
class Statement  : public Node{
  virtual void Accept(ASTVisitor& v) = 0;
};

class Block : public Expression {
public:
    std::vector<Statement> statements;
    Block() { }
    
    void Accept(ASTVisitor& v){ v.Visit(*this); }
};

/////////////////////////////////////////////////////////
// Statement

class ExpressionStatement : public Statement {
public:
    Expression& expression;
    ExpressionStatement(Expression& expression) : 
        expression(expression) { }
        
    void Accept(ASTVisitor& v){ v.Visit(*this); }
};

/////////////////////////////////////////////////////////
// Expression
class Literal : public Expression {
public:
    uint32_t value;
    Literal(uint32_t const &value) : value(value) { }
    void Accept(ASTVisitor& v){ v.Visit(*this); }
};



class BinaryOp : public Expression {
public:
    int op;
    Expression& lhs;
    Expression& rhs;
    BinaryOp(Expression &lhs, int op, Expression &rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
    void Accept(ASTVisitor& v){ v.Visit(*this); }
};


// };  //end namespace AST_Nodes