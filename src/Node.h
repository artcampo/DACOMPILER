#pragma once
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
    
};

class Expression : public Node{};
class Statement  : public Node{};

class Block : public Expression {
public:
    std::vector<Statement> statements;
    Block() { }
};

/////////////////////////////////////////////////////////
// Statement

class ExpressionStatement : public Statement {
public:
    Expression& expression;
    ExpressionStatement(Expression& expression) : 
        expression(expression) { }
};

/////////////////////////////////////////////////////////
// Expression
class Literal : public Expression {
public:
    uint32_t value;
    Literal(uint32_t const &value) : value(value) { }
};



class BinaryOp : public Expression {
public:
    int op;
    Expression& lhs;
    Expression& rhs;
    BinaryOp(Expression &lhs, int op, Expression &rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
};


// };  //end namespace AST_Nodes