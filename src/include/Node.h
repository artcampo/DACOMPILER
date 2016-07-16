#pragma once
// #include "ASTVisitor.hpp"
#include <iostream>
#include <vector>
#include <stdint.h>


class ASTVisitor;

// namespace AST_Nodes{

class Node {
public:
    Node(){
//       std::cout << "Node Ctor"<<std::endl;
    }
    virtual ~Node() {}
    
    virtual void Accept(ASTVisitor& v){std::cout << "Accept on Node";};
    
};

class Expression : public Node{
public:  
  Expression(){
//     std::cout << "Expression Ctor" <<std::endl;
  }
  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Expression";};
};
class Statement  : public Node{
public:  
  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Statement";};
};

/////////////////////////////////////////////////////////
class Block : public Expression {
public:
    std::vector<Statement*> statements;
    Block() {
//       std::cout << "Block Ctor" <<std::endl;
    }
    
    void Accept(ASTVisitor& v);
};

/////////////////////////////////////////////////////////
class ExpressionStatement : public Statement {
public:
    Expression* expression;
    ExpressionStatement(Expression* expression) : 
        expression(expression) {
//           std::cout << "ExpressionStatement Ctor" <<std::endl;
          
        }
        
    void Accept(ASTVisitor& v);
};

/////////////////////////////////////////////////////////
class Literal : public Expression {
public:
    uint32_t value;
    Literal(uint32_t const &value) : value(value){
//       std::cout << "Literal Ctor" <<std::endl;
    }
    void Accept(ASTVisitor& v);
};


/////////////////////////////////////////////////////////
class BinaryOp : public Expression {
public:
    int op;
    Expression* lhs;
    Expression* rhs;
    BinaryOp(Expression *lhs, int op, Expression *rhs) :
        lhs(lhs), rhs(rhs), op(op) {
//           std::cout << "BinaryOp Ctor" <<std::endl;
        }
    void Accept(ASTVisitor& v);
};


// };  //end namespace AST_Nodes