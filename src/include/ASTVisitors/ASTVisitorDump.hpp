#pragma once
#include "ASTVisitor.hpp"
#include "Node.hpp"
#include "CompilationUnit.hpp"

namespace Compiler{
namespace AST{

class ASTVisitorDump : public ASTVisitor{
public:
  virtual void Visit(ProgBody const& p);
  virtual void Visit(ProgInit const& p);
  virtual void Visit(ProgEnd const& p);
  virtual void Visit(FuncDef const& p);
  virtual void Visit(Block const& p);
  virtual void Visit(IfStmt const& p);
  virtual void Visit(WhileStmt const& p);
  virtual void Visit(Literal const& p);
  virtual void Visit(BinaryOp const& p);
  virtual void Visit(DeclStmt const& p);
  virtual void Visit(VarDeclList const& p);
  virtual void Visit(VarDecl const& p);
  virtual void Visit(AssignStmt const& p);
  virtual void Visit(Var const& p);
  virtual void Visit(RefOp const& p);
  virtual void Visit(DerefOp const& p);
  virtual void Visit(FuncCall const& p);
  virtual void Visit(FuncRet const& p);
  virtual void Visit(ReturnStmt const& p);
  virtual void Visit(ClassDef const& p);
  virtual void Visit(VarName const& p);



  ASTVisitorDump(CompilationUnit& unit, const bool show_attributes = false)
    :  unit_(unit), indent_(1), show_attributes_(show_attributes){};

private:
  void Indent();
  void IncreaseIndent();
  void DecreaseIndent();
  void DisplayAttributes(Node const& p);
  void DumpSymbolTable();

  int  indent_;
  bool show_attributes_;
  CompilationUnit&  unit_;
};

}//end namespace AST
}//end namespace Compiler
