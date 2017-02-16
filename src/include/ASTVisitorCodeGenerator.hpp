#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"
#include "CodeGenerator/RegisterAllocator.hpp"
#include "ByteCode.hpp"
#include "Utils.hpp"
#include <map>

namespace Compiler{
namespace AST{

class ASTVisitorCodeGenerator : public ASTVisitor{
public:
    virtual void Visit(Block const& p);
    virtual void Visit(IfStmt const& p);
    virtual void Visit(Literal const& p);
    virtual void Visit(BinaryOp const& p);
    virtual void Visit(DeclStmt const& p){};
    virtual void Visit(VarDeclList const& p){};
    virtual void Visit(VarDecl const& p){};
    virtual void Visit(AssignStmt const& p){};
    virtual void Visit(Var const& p){};

    ASTVisitorCodeGenerator() : reg_allocator_(){};

    void EndOfProgram();
    void Print() const;

    ByteCode const& byte_code() const{ return byte_code_;};
private:
    CodeGenerator::RegisterAllocator  reg_allocator_;
    std::map<const Node*,uint32_t>    reg_of_Expr_;
    ByteCode                          byte_code_;

};

}//end namespace AST
}//end namespace Compiler
