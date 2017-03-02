#include "ASTVisitors/ASTVisitorDump.hpp"

namespace Compiler{
namespace AST{

void ASTVisitorDump::Visit(ProgBody const& p){
  p.GetProgInit().Accept(*this);
  p.GetMainFunc().Accept(*this);
  p.GetProgEnd().Accept(*this);
}

void ASTVisitorDump::Visit(FuncDecl const& p){
  p.GetBody().Accept(*this);
}

void ASTVisitorDump::Visit(ProgInit const& p){

}

void ASTVisitorDump::Visit(ProgEnd const& p){

}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(Block const& p) {
//   std::cout << "Stmts:\n";
  for (auto& c : p.statements_){
      Indent();
      c->Accept(*this);
      std::cout << std::endl;
  }
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(Literal const& p){
  std::cout << "Literal: ";
  std::cout << p.Value();
  DisplayAttributes(p);
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(BinaryOp const& p){
  std::cout << "Op:" << p.OpString(); DisplayAttributes(p); std::cout <<"\n";
  IncreaseIndent();
  Indent();
  p.Lhs().Accept(*this);
  std::cout << "\n";
  Indent();
  p.Rhs().Accept(*this);

  DecreaseIndent();
}

/////////////////////////////////////////////////////////////////////////////
void ASTVisitorDump::Visit(IfStmt const& p){
  std::cout << "IfStmt:\n";

  IncreaseIndent();Indent();std::cout << "Cond: ";

  p.GetCond().Accept(*this); std::cout << "\n";

  Indent();std::cout << "Then:\n";
  IncreaseIndent(); p.GetThen().Accept(*this); DecreaseIndent();

  if(p.HasElse()){
    Indent();std::cout << "Else:\n";
    IncreaseIndent(); p.GetElse().Accept(*this); DecreaseIndent();
  }
  DecreaseIndent();
}

void ASTVisitorDump::Visit(WhileStmt const& p){
  //  p.GetBody().Accept(*this);
  std::cout << "WhileStmt:\n";
  IncreaseIndent(); Indent();std::cout << "Cond: ";
  p.GetCond().Accept(*this); std::cout << "\n";
  Indent();std::cout << "Body:\n";
  IncreaseIndent();p.GetBody().Accept(*this);DecreaseIndent();
}

void ASTVisitorDump::Visit(DeclStmt const& p){
  p.GetVarDeclList().Accept(*this);
}
void ASTVisitorDump::Visit(VarDeclList const& p){
  for(const auto& it : p.GetVarDeclVector()){
//     Indent();
    it->Accept(*this);
    std::cout << " ";
  }
}
void ASTVisitorDump::Visit(VarDecl const& p){
  std::cout << p.str();
}

void ASTVisitorDump::Visit(AssignStmt const& p){
  std::cout << "Assign"; DisplayAttributes(p); std::cout<<"\n";
  IncreaseIndent();
  Indent(); p.Lhs().Accept(*this); std::cout << "\n";
  Indent(); p.Rhs().Accept(*this);
  DecreaseIndent();
}

void ASTVisitorDump::Visit(Var const& p){
  std::cout << p.str(); DisplayAttributes(p);
}

void ASTVisitorDump::Visit(RefOp const& p){
  std::cout << p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.Rhs().Accept(*this); DecreaseIndent();
}

void ASTVisitorDump::Visit(DerefOp const& p){
  std::cout << p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.Rhs().Accept(*this); DecreaseIndent();
}


void ASTVisitorDump::Indent(){
  for(int i = 0; i < indent_; ++i) std::cout<< "-";
}

void ASTVisitorDump::IncreaseIndent(){
  indent_ += 1;
}
void ASTVisitorDump::DecreaseIndent(){
  if(indent_ > 0) indent_ -= 1;
}

void ASTVisitorDump::DisplayAttributes(Node const& p){
  if(show_attributes_){
    auto it = unit_.type_of_node_.find(&p);
    bool display = (it != unit_.type_of_node_.end()) or unit_.HasLRness(p);
    if(display) std::cout << " [";
    if(it != unit_.type_of_node_.end()) std::cout << it->second->str();

    if(unit_.HasLRness(p)) std::cout << " " << unit_.LRnessStr(p);
    if(display) std::cout << "]";
  }
}

}//end namespace AST
}//end namespace Compiler