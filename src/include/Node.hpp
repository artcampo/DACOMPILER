#pragma once
// #include "ASTVisitor.hpp"
#include <iostream>
#include <vector>
#include <stdint.h>
#include <memory>
#include "Types.hpp"


namespace Compiler{
namespace AST{

class ASTVisitor;

class Node;
class Expr;
class DeclStmt;
class VarDeclList;
class VarDecl;
class AssignStmt;
  
class Node {
public:
    Node(){
//       std::cout << "Node Ctor"<<std::endl;
    }
    virtual ~Node() {}
    
    virtual void Accept(ASTVisitor& v){std::cout << "Accept on Node";};
    virtual std::string str() const = 0;
    
};

class Expr : public Node{
public:  
//   Expr(){}
  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Expr";};
  virtual std::string str() const = 0;
};

/////////////////////////////////////////////////////////
class Statement  : public Node{
public:  
  Statement(){};
  virtual void Accept(ASTVisitor& v){std::cout << "Accept on Statement";};
  virtual std::string str() const = 0;
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
    virtual std::string str() const{ return std::string("string not implemented");};
};

/////////////////////////////////////////////////////////
class ExprStmt : public Statement {
public:
  ExprStmt(Expr* const expr) : expr_(expr) {}
        
  Expr* const GetExpr() const { return expr_;}
  void Accept(ASTVisitor& v);
  virtual std::string str() const{ return std::string("string not implemented");};
private:
  Expr* expr_;
};

/////////////////////////////////////////////////////////
class IfStmt : public Statement {
public:
  IfStmt(Expr* const condition, Block* const block1, Block* const block2) 
   : condition_(condition), block1_(block1), block2_(block2){}
      
  IfStmt(Expr* const condition, Block* const block1) 
  : condition_(condition), block1_(block1), block2_(nullptr){}      
        
  void Accept(ASTVisitor& v);
    
  Expr* GetCond() const noexcept{ return condition_;};
  Block* GetThen() const noexcept{ return block1_;};
  Block* GetElse() const noexcept{ return block2_;};
  const bool HasElse()const noexcept{ return block2_ != nullptr;};
  virtual std::string str() const{ return std::string("string not implemented");};
  
private:    
  Expr* condition_;
  Block*  block1_;
  Block*  block2_;    
};

/////////////////////////////////////////////////////////
class AssignStmt : public Statement {
public:
  AssignStmt(Expr* const lhs, Expr* const rhs)
    : lhs_(lhs), rhs_(rhs) {}      
  void Accept(ASTVisitor& v);
  
  Expr* const GetLhs() const noexcept{return lhs_.get();}
  Expr* const GetRhs() const noexcept{return rhs_.get();}
  
  virtual std::string str() const{
    return lhs_->str() + "=" + rhs_->str();
  };
private:
  std::unique_ptr<Expr> lhs_;
  std::unique_ptr<Expr> rhs_;
};

/////////////////////////////////////////////////////////
class DeclStmt : public Statement {
public:
  DeclStmt(VarDeclList* const decl_list): decl_list_(decl_list) {}      
  void Accept(ASTVisitor& v);
  VarDeclList* const GetVarDeclList() const noexcept{return decl_list_;}
  
  virtual std::string str() const{ return std::string("string not implemented");};
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
  virtual std::string str() const{ return std::string("string not implemented");};
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
class Literal : public Expr {
public:
    uint32_t value;
    Literal(const uint32_t &value) : value(value){
//       std::cout << "Literal Ctor" <<std::endl;
    }
    void Accept(ASTVisitor& v);
    std::string str() const noexcept{
      return std::to_string(value);
    }
};


/////////////////////////////////////////////////////////
class BinaryOp : public Expr {
public:
    int op;
    Expr* lhs;
    Expr* rhs;
    //TODO change op to own type
    BinaryOp(Expr* const lhs, const int op, Expr* const rhs) :
        lhs(lhs), rhs(rhs), op(op) {
//           std::cout << "BinaryOp Ctor" <<std::endl;
        }
    void Accept(ASTVisitor& v);
    
    std::string OpString() const noexcept;
    
    std::string str() const noexcept{
      return OpString();
    }
};


/////////////////////////////////////////////////////////
class Var : public Expr{
public:  
  
  Var(const std::string& name): name_(name){}
  virtual void Accept(ASTVisitor& v);
  
  std::string str() const noexcept{
    return name_;
  }
  
private:  
  const std::string name_;
};

}//end namespace AST
}//end namespace Compiler
