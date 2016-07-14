#pragma once
#include "ASTVisitor.hpp"
#include "Node.h"

class ASTVisitorPrettyPrinter : public ASTVisitor{
public:
    virtual bool ActBefore(Block const& p);
    virtual void ActAfter (Block const& p);
    virtual bool ActBefore(ExpressionStatement const& p);
    virtual void ActAfter (ExpressionStatement const& p);    
    virtual bool ActBefore(Literal const& p);
    virtual void ActAfter (Literal const& p);     
    virtual bool ActBefore(BinaryOp const& p);
    virtual void ActAfter (BinaryOp const& p);        

    virtual void Visit(Block const& p);
    virtual void Visit(ExpressionStatement const& p);
    virtual void Visit(Literal const& p);
    virtual void Visit(BinaryOp const& p);
};