#include "ASTVisitors/Dump.hpp"

namespace Compiler{
namespace AST{

void Dump::Visit(ProgBody const& p){
  p.GetProgInit().Accept(*this);
  for(auto& it : p) { Indent(); it->Accept(*this); }
  for(auto& it : p.GetClassDefs() ) { Indent(); it->Accept(*this);}
  p.GetProgEnd().Accept(*this);
}

void Dump::Visit(FuncDef const& p){
  std::cout << p.str()<<"\n";
  IncreaseIndent(); //Indent();
  p.GetBody().Accept(*this);
  DecreaseIndent();
}

void Dump::Visit(ClassDef const& p){
  std::cout << p.str()<<"\n";
  /*
  IncreaseIndent(); Indent();
  p.¿?.Accept(*this);   //hahahah, that's an operator to implement '¿?'
  DecreaseIndent();
  */
}

void Dump::Visit(ProgInit const& p){

}

void Dump::Visit(ProgEnd const& p){
  DumpSymbolTable();
}

/////////////////////////////////////////////////////////////////////////////
void Dump::Visit(Block const& p) {
//   std::cout << "Stmts:\n";
  for (auto& c : p.statements_){
      Indent();
      c->Accept(*this);
      std::cout << std::endl;
  }
}

/////////////////////////////////////////////////////////////////////////////
void Dump::Visit(Literal const& p){
  std::cout << "Literal: ";
  std::cout << p.Value();
  DisplayAttributes(p);
}

/////////////////////////////////////////////////////////////////////////////
void Dump::Visit(BinaryOp const& p){
  std::cout << "Op:" << p.OpString(); DisplayAttributes(p); std::cout <<"\n";
  IncreaseIndent();
  Indent(); p.Lhs().Accept(*this); std::cout << "\n";
  Indent(); p.Rhs().Accept(*this);

  DecreaseIndent();
}

/////////////////////////////////////////////////////////////////////////////
void Dump::Visit(IfStmt const& p){
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

void Dump::Visit(WhileStmt const& p){
  //  p.GetBody().Accept(*this);
  std::cout << "WhileStmt:\n";
  IncreaseIndent(); Indent();std::cout << "Cond: ";
  p.GetCond().Accept(*this); std::cout << "\n";
  Indent();std::cout << "Body:\n";
  IncreaseIndent();p.GetBody().Accept(*this);DecreaseIndent();
}

void Dump::Visit(DeclStmt const& p){
  p.GetVarDeclList().Accept(*this);
}
void Dump::Visit(VarDeclList const& p){
  for(const auto& it : p.GetVarDeclVector()){
//     Indent();
    it->Accept(*this);
    std::cout << " ";
  }
}
void Dump::Visit(VarDecl const& p){
  std::cout << p.str();
}

void Dump::Visit(AssignStmt const& p){
  std::cout << "Assign"; DisplayAttributes(p); std::cout<<"\n";
  IncreaseIndent();
  Indent(); p.Lhs().Accept(*this); std::cout << "\n";
  Indent(); p.Rhs().Accept(*this);
  DecreaseIndent();
}

void Dump::Visit(Var const& p){
  std::cout << p.str(); DisplayAttributes(p);
}

void Dump::Visit(RefOp const& p){
  std::cout << p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.Rhs().Accept(*this); DecreaseIndent();
}

void Dump::Visit(DerefOp const& p){
  std::cout << p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.Rhs().Accept(*this); DecreaseIndent();
}

void Dump::Visit(FuncCall& p){
  std::cout << p.str(); DisplayAttributes(p);std::cout << "\n";

  //Dump receiver
  IncreaseIndent(); Indent(); p.Receiver().Accept(*this); DecreaseIndent();std::cout << "\n";

  //Dump args
//   IncreaseIndent();
  bool first_arg = true;
  for(const auto& it : p){
    if(not first_arg)std::cout << "\n";
    IncreaseIndent(); Indent(); it->Accept(*this); DecreaseIndent();
    first_arg = false;
  }
//   DecreaseIndent();
}

void Dump::Visit(FuncRet& p){
  std::cout << p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.GetCall().Accept(*this); DecreaseIndent();
}

void Dump::Visit(ReturnStmt const& p){
  std::cout << p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.RetExpr().Accept(*this); DecreaseIndent();
}

void Dump::Visit(VarName const& p){
  std::cout << p.str(); DisplayAttributes(p);
}

void Dump::Visit(DotOp const& p){
  std::cout << p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.Lhs().Accept(*this); DecreaseIndent();std::cout << "\n";
  IncreaseIndent(); Indent(); p.Rhs().Accept(*this); DecreaseIndent();
}



void Dump::Indent(){
  for(int i = 0; i < indent_; ++i) std::cout<< "-";
}

void Dump::IncreaseIndent(){
  indent_ += 1;
}
void Dump::DecreaseIndent(){
  if(indent_ > 0) indent_ -= 1;
}

void Dump::DisplayAttributes(Node const& p){
  if(show_attributes_){
    auto it = unit_.type_of_node_.find(&p);
    bool display = (it != unit_.type_of_node_.end()) or unit_.HasLRness(p)
      or unit_.HasReadWrite(p) or  unit_.HasVarUsage(p);
    if(display) std::cout << " [";
    if(it != unit_.type_of_node_.end()) std::cout << it->second->str();

    if(unit_.HasLRness(p)) std::cout << " " << unit_.LRnessStr(p);
    if(unit_.HasReadWrite(p)) std::cout << " " << unit_.ReadWriteStr(p);
    if(unit_.HasVarUsage(p)) std::cout << " " << unit_.VarUsageStr(p);
    if(display) std::cout << "]";
  }
}

void Dump::DumpSymbolTable(){
  /*
  //This should only list the module's functions
  std::cout << "Symbol Table:\n";
  for(auto& it : unit_.symbol_table_){
    std::cout << it.first
              << " id: " << it.second
              << " decl: " << unit_.module_declaration_table_[it.second]->str()
              << "\n";
  }
  std::cout << "end Symbol Table:\n";
  */

  std::cout << "\n\nDeclaration Table:\n";
  for(auto& it : unit_.module_declaration_table_){
    std::cout << it.first << ": " <<it.second->str()<<"\n";
  }
}

}//end namespace AST
}//end namespace Compiler
