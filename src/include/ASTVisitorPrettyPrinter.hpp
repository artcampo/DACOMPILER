#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"

class ASTVisitorPrettyPrinter : public ASTVisitor{
public:
    virtual void Visit(Block const& p);
    virtual void Visit(ExpressionStatement const& p);
    virtual void Visit(Literal const& p);
    virtual void Visit(BinaryOp const& p);
};