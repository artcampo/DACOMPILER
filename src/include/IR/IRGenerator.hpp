#pragma once
#include "AST/Node.hpp"
#include "Types.hpp"
#include "CompilationUnit.hpp"
#include "AST/ASTVisitor.hpp"
#include "IR/IRStream.hpp"
#include <map>
#include <vector>

namespace Compiler{
namespace AST{

using IR::PtrIRStream;

/*
 * While this is an ASTVisitor it has been set apart for one reasons
 * It needs one extra parameter for the successor inherited value
 * (this could have been stored in the visitor itself, but would have
 * made the implementation of each function more complex, when this is
 * the visitor of already higher complexity).
*/

class IRGenerator{
public:

  IRGenerator(CompilationUnit& unit): unit_(unit), emit_addr_var_inht_(false)
    ,inside_member_func_def_(false){};

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
  virtual void Visit(FuncCall& p, const Node* successor);
  virtual void Visit(FuncRet& p, const Node* successor);
  virtual void Visit(ReturnStmt const& p, const Node* successor);
  virtual void Visit(ClassDef const& p, const Node* successor);
  virtual void Visit(VarName const& p, const Node* successor);
  virtual void Visit(DotOp const& p, const Node* successor);



  void EndOfProgram();
private:
  CompilationUnit&  unit_;
  std::vector<PtrIRStream> streams_;
  IR::IRStream* current_stream_;

  //reg destination of Node
  std::map<const Node*, IR::Reg>    reg_dst_of_expr_;
  //reg source of Node (not sparsingly used)
  std::map<const Node*, IR::Reg>    reg_src_of_expr_;
  //only used for the src of assignment's lhs
  std::map<const Node*, IR::Reg>    reg_src_of_assignment_;

  std::map<const Node*, std::vector<IR::Addr>> back_patch_;

  std::map<const Node*, IR::MemAddr> addr_of_var_;

  IR::Label   local_label_inht_;    //label of current function's locals
  IR::Label   class_label_inht_;    //label of current class this
  Class*      class_inht_;          //current class being processed
  bool        emit_addr_var_inht_;
  bool        is_member_call_inht_; //only within funcRet/funcCall
  bool        inside_member_func_def_;

  IR::IRStream& CurrentStream() const noexcept{ return *current_stream_;}
  void BackPatch(const Node& n, const IR::Addr position);
  void AddToBackPatch(const Node& n, const IR::Addr position);
  void PrintBackPatch();
  void Print() const noexcept;

  void NewStream(const Label& entry_label){
    streams_.push_back( std::move(
      std::make_unique<IR::IRStream>(entry_label) ));
    current_stream_ = streams_.back().get();
  }

};



}//end namespace AST
}//end namespace Compiler
