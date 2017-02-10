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

/////////////////////////////////////////////////////////
class Statement  : public Node{
public:  
  Statement(){};
  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Statement";};
};

/////////////////////////////////////////////////////////
class Block : public Node {
public:
    std::vector<Statement*> statements;
    Block() {
//       std::cout << "Block Ctor" <<std::endl;
    }
    void AddStatement(Statement* const s){ statements.push_back(s);}

    Statement* FirstStatement(){return statements[0];}
    Statement* const FirstStatement() const{return statements[0];}
    
    void Accept(ASTVisitor& v);
};

/////////////////////////////////////////////////////////
class ExpressionStatement : public Statement {
public:
    Expression* expression;
    ExpressionStatement(Expression* const expression) : 
        expression(expression) {
//           std::cout << "ExpressionStatement Ctor" <<std::endl;
          
        }
        
    void Accept(ASTVisitor& v);
};

/////////////////////////////////////////////////////////
class StmtIf : public Statement {
public:
    Expression* condition_;
    Block*  block1_;
    Block*  block2_;
    StmtIf(Expression* const condition
              , Block* const block1
              , Block* const block2) 
      : condition_(condition)
      , block1_(block1)
      , block2_(block2){}
        
    void Accept(ASTVisitor& v);
};

/////////////////////////////////////////////////////////
class Literal : public Expression {
public:
    uint32_t value;
    Literal(const uint32_t &value) : value(value){
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
    //TODO change op to own type
    BinaryOp(Expression* const lhs, const int op, Expression* const rhs) :
        lhs(lhs), rhs(rhs), op(op) {
//           std::cout << "BinaryOp Ctor" <<std::endl;
        }
    void Accept(ASTVisitor& v);
    
    std::string OpString() const noexcept;
};


// };  //end namespace AST_Nodes
