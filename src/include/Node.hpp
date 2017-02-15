#pragma once
// #include "ASTVisitor.hpp"
#include <iostream>
#include <vector>
#include <stdint.h>
#include "Types.hpp"


namespace Compiler{
namespace AST{

class ASTVisitor;

class Node;
class Expression;
class DeclStmt;
class VarDeclList;
class VarDecl;
  
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
  StmtIf(Expression* const condition, Block* const block1, Block* const block2) 
   : condition_(condition), block1_(block1), block2_(block2){}
      
  StmtIf(Expression* const condition, Block* const block1) 
  : condition_(condition), block1_(block1), block2_(nullptr){}      
        
  void Accept(ASTVisitor& v);
    
  Expression* GetCond() const noexcept{ return condition_;};
  Block* GetThen() const noexcept{ return block1_;};
  Block* GetElse() const noexcept{ return block2_;};
  const bool HasElse()const noexcept{ return block2_ != nullptr;};
    
private:    
  Expression* condition_;
  Block*  block1_;
  Block*  block2_;    
};

/////////////////////////////////////////////////////////
class DeclStmt : public Statement {
public:
  DeclStmt(VarDeclList* const decl_list): decl_list_(decl_list) {}      
  void Accept(ASTVisitor& v);
  VarDeclList* const GetVarDeclList() const noexcept{return decl_list_;}
  
private:
  VarDeclList* decl_list_;
};


/////////////////////////////////////////////////////////
class VarDeclList : public Node{
public:  
  
  VarDeclList(const std::vector<VarDecl*>& list): list_(list) {}
  virtual void Accept(ASTVisitor& v);
  
  std::vector<VarDecl*>& GetVarDeclVector() noexcept{return list_;};
  const std::vector<VarDecl*>& GetVarDeclVector() const noexcept{return list_;};
private:
  std::vector<VarDecl*> list_;  
};

/////////////////////////////////////////////////////////
class VarDecl : public Node{
public:  
  
  VarDecl(const std::string& name, const TypeId& typeId)
    : name_(name), typeId_(typeId){}
  virtual void Accept(ASTVisitor& v);
  
  std::string str() const noexcept{
    std::string s;
    s += typeId_.str();
    s += " ";
    s += name_;
    return s;
  }
  
private:  
  const std::string name_;
  const TypeId typeId_;
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


}//end namespace AST
}//end namespace Compiler
