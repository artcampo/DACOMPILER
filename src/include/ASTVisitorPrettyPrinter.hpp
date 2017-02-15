#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"

namespace Compiler{
namespace AST{  

class ASTVisitorPrettyPrinter : public ASTVisitor{
public:
    virtual void Visit(Block const& p);
    virtual void Visit(IfStmt const& p);
    virtual void Visit(ExprStmt const& p);
    virtual void Visit(Literal const& p);
    virtual void Visit(BinaryOp const& p);
    virtual void Visit(DeclStmt const& p);
    virtual void Visit(VarDeclList const& p);
    virtual void Visit(VarDecl const& p);    
    virtual void Visit(AssignStmt const& p);
    virtual void Visit(Var const& p);
    
    ASTVisitorPrettyPrinter(): indent_(0){};
    
private:
    void Indent();
    void IncreaseIndent();
    void DecreaseIndent();
    
    int  indent_;
};

}//end namespace AST
}//end namespace Compiler
