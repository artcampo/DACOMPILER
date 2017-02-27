#pragma once
#include "Node.hpp"
#include "Types.hpp"
#include "CompilationUnit.hpp"
#include "ASTVisitor.hpp"
#include "IR/IRStream.hpp"
#include <map>

namespace Compiler{

using namespace AST;

class ASTVisitorIRGenerator : public ASTVisitor{
public:

  ASTVisitorIRGenerator(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(ProgBody const& p);
  virtual void Visit(ProgInit const& p);
  virtual void Visit(ProgEnd const& p);
  virtual void Visit(Block const& p);
  virtual void Visit(IfStmt const& p);
  virtual void Visit(WhileStmt const& p);
  virtual void Visit(BinaryOp const& p);
  virtual void Visit(AssignStmt const& p);
  virtual void Visit(RefOp const& p);
  virtual void Visit(DerefOp const& p);
  virtual void Visit(Literal const& p);
  virtual void Visit(Var const& p);
  virtual void Visit(DeclStmt const& p);
  virtual void Visit(VarDeclList const& p);
  virtual void Visit(VarDecl const& p);

private:
  CompilationUnit&  unit_;

  std::map<const Node*, std::vector<IR::Addr>> back_patch_;

  void BackPatch(const Node& n, const IR::Addr position);
  void AddToBackPatch(const Node& n, const IR::Addr position);
  void PrintBackPatch();
};



}//end namespace Compiler
