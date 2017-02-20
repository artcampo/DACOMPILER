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
  virtual void Visit(ProgBody const& p, const Node* successor);
  virtual void Visit(ProgInit const& p, const Node* successor);
  virtual void Visit(ProgEnd const& p, const Node* successor);
  virtual void Visit(Block const& p, const Node* successor);

  virtual void Visit(IfStmt const& p, const Node* successor);
  virtual void Visit(Literal const& p, const Node* successor);
  virtual void Visit(BinaryOp const& p, const Node* successor);
  virtual void Visit(DeclStmt const& p, const Node* successor);
  virtual void Visit(VarDeclList const& p, const Node* successor){};
  virtual void Visit(VarDecl const& p, const Node* successor){};
  virtual void Visit(AssignStmt const& p, const Node* successor);
  virtual void Visit(Var const& p, const Node* successor){};

  CodeGen() : reg_allocator_(){};

  void EndOfProgram();
  void Print() const;

  ByteCode const& byte_code() const{ return byte_code_;};

private:
  CodeGenerator::RegisterAllocator  reg_allocator_;
  std::map<const Node*,uint32_t>    reg_of_Expr_;
  ByteCode                          byte_code_;

  //Node has to backpatch inst at position VM::Addr
  std::map<const Node*, std::vector<VM::Addr>> back_patch_;

  void BackPatch(const Node* n, const VM::Addr position);
  void AddToBackPatch(const Node* n, const VM::Addr position);
  void PrintBackPatch();
};

}//end namespace AST
}//end namespace Compiler
