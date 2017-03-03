#pragma once
#include "Node.hpp"
#include "Types.hpp"
#include "CompilationUnit.hpp"
#include "ASTVisitor.hpp"
#include "IR/IRStream.hpp"
#include <map>

namespace Compiler{
namespace AST{


class IRGenerator{
public:

  IRGenerator(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(ProgBody const& p, const Node* successor);
  virtual void Visit(ProgInit const& p, const Node* successor);
  virtual void Visit(ProgEnd const& p, const Node* successor);
  virtual void Visit(FuncDef const& p, const Node* successor);
  virtual void Visit(Block const& p, const Node* successor);
  virtual void Visit(IfStmt const& p, const Node* successor);
  virtual void Visit(WhileStmt const& p, const Node* successor);
  virtual void Visit(BinaryOp const& p, const Node* successor);
  virtual void Visit(AssignStmt const& p, const Node* successor);
  virtual void Visit(RefOp const& p, const Node* successor);
  virtual void Visit(DerefOp const& p, const Node* successor);
  virtual void Visit(Literal const& p, const Node* successor);
  virtual void Visit(Var const& p, const Node* successor);
  virtual void Visit(DeclStmt const& p, const Node* successor);
  virtual void Visit(VarDeclList const& p, const Node* successor);
  virtual void Visit(VarDecl const& p, const Node* successor);

  void EndOfProgram();
private:
  CompilationUnit&  unit_;
  IR::IRStream      stream_;

  //reg destination of Node
  std::map<const Node*, IR::Reg>    reg_dst_of_expr_;
  //reg source of Node (not sparsingly used)
  std::map<const Node*, IR::Reg>    reg_src_of_expr_;
  //only used for the src of assignment's lhs
  std::map<const Node*, IR::Reg>    reg_src_of_assignment_;

  std::map<const Node*, std::vector<IR::Addr>> back_patch_;

  std::map<const Node*, IR::MemAddr> addr_of_var_;


  void BackPatch(const Node& n, const IR::Addr position);
  void AddToBackPatch(const Node& n, const IR::Addr position);
  void PrintBackPatch();
  void Print() const noexcept;


};



}//end namespace AST
}//end namespace Compiler
