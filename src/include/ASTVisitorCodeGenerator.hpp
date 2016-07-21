#pragma once
#include "ASTVisitor.hpp"
#include "Node.h"
#include "CodeGenerator/RegisterAllocator.hpp"
#include "ByteCode.h"
#include <map>

class ASTVisitorCodeGenerator : public ASTVisitor{
public:
    virtual void Visit(Block const& p);
    virtual void Visit(ExpressionStatement const& p);
    virtual void Visit(Literal const& p);
    virtual void Visit(BinaryOp const& p);
    
    ASTVisitorCodeGenerator() : reg_allocator_(){};
    
    void EndOfProgram();
    void Print() const;
private:
    CodeGenerator::RegisterAllocator  reg_allocator_;
    std::map<const Node*,uint32_t>    reg_of_expression_;
    ByteCode                          byte_code_;
};