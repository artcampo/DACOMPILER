#pragma once
#include "AST.hpp"
#include "Node.hpp"

namespace Compiler{
namespace AST{  
  
class ASTVisitor{
public: 

    virtual void Visit(Block const& p) = 0;
    virtual void Visit(ExpressionStatement const& p) = 0;
    virtual void Visit(StmtIf const& p) = 0;
    virtual void Visit(Literal const& p) = 0;
    virtual void Visit(BinaryOp const& p) = 0;
    virtual void Visit(DeclStmt const& p) = 0;
    virtual void Visit(VarDeclList const& p) = 0;
    virtual void Visit(VarDecl const& p) = 0;
    
};

}//end namespace AST
}//end namespace Compiler
