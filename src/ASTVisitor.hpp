#pragma once
#include "AST.hpp"
#include "Node.h"

class ASTVisitor{
public:
    virtual bool ActBefore(Block const& p) = 0;
    virtual void ActAfter (Block const& p) = 0;
    virtual bool ActBefore(ExpressionStatement const& p) = 0;
    virtual void ActAfter (ExpressionStatement const& p) = 0;    
    virtual bool ActBefore(Literal const& p) = 0;
    virtual void ActAfter (Literal const& p) = 0;     
    virtual bool ActBefore(BinaryOp const& p) = 0;
    virtual void ActAfter (BinaryOp const& p) = 0;        

    virtual void Visit(Block const& p) = 0;
    virtual void Visit(ExpressionStatement const& p) = 0;
    virtual void Visit(Literal const& p) = 0;
    virtual void Visit(BinaryOp const& p) = 0;
    
};