#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"

class ASTVisitorDump : public ASTVisitor{
public:
    virtual void Visit(Block const& p);
    virtual void Visit(StmtIf const& p);
    virtual void Visit(ExpressionStatement const& p);
    virtual void Visit(Literal const& p);
    virtual void Visit(BinaryOp const& p);
    
    ASTVisitorDump(): indent_(0){};
    
private:
    void Indent();
    void IncreaseIndent();
    void DecreaseIndent();
    
    int  indent_;
};
