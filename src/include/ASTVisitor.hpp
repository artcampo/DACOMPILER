#pragma once
#include "AST.hpp"
#include "Node.hpp"

class ASTVisitor{
public: 

    virtual void Visit(Block const& p) = 0;
    virtual void Visit(ExpressionStatement const& p) = 0;
    virtual void Visit(Literal const& p) = 0;
    virtual void Visit(BinaryOp const& p) = 0;
    
};