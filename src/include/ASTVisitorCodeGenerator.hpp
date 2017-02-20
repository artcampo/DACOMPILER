#pragma once
#include "Node.hpp"
#include "CodeGenerator/RegisterAllocator.hpp"
#include "ByteCode.hpp"
#include "Utils.hpp"
#include <map>
#include <stack>
#include <cstddef>


namespace Compiler{
namespace AST{


class CodeGen{
public:
    virtual void Visit(Block const& p, const Statement* successor);

    virtual void Visit(IfStmt const& p, const Statement* successor);
    virtual void Visit(Literal const& p, const Statement* successor);
    virtual void Visit(BinaryOp const& p, const Statement* successor);
    virtual void Visit(DeclStmt const& p, const Statement* successor);
    virtual void Visit(VarDeclList const& p, const Statement* successor){};
    virtual void Visit(VarDecl const& p, const Statement* successor){};
    virtual void Visit(AssignStmt const& p, const Statement* successor);
    virtual void Visit(Var const& p, const Statement* successor){};

    CodeGen() : reg_allocator_(){};

    void EndOfProgram();
    void Print() const;

    ByteCode const& byte_code() const{ return byte_code_;};
private:
    CodeGenerator::RegisterAllocator  reg_allocator_;
    std::map<const Node*,uint32_t>    reg_of_Expr_;
    ByteCode                          byte_code_;
    std::stack<const Node*> back_patch_;

};

}//end namespace AST
}//end namespace Compiler
