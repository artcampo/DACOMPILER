#include "ASTVisitors/Dump.hpp"

namespace Compiler{
namespace AST{

void Dump::Visit(ProgBody const& p){
  p.GetProgInit().Accept(*this);
  for(auto& it : p.GetClassDefs() ) { Indent(); it->Accept(*this);}
  for(auto& it : p) { Indent(); it->Accept(*this); }
  p.GetProgEnd().Accept(*this);
}

void Dump::Visit(FuncDef const& p){
  std::cout << "[FDef] " << p.str()<<"\n";
  IncreaseIndent(); //Indent();
  p.GetBody().Accept(*this);
  DecreaseIndent();
}

void Dump::Visit(ClassDef const& p){
//   std::cout << "[CDef] " << p.str(); 
  std::cout << "[CDef] " << unit_.GetClass(
    dynamic_cast<const ClassType&>(unit_.GetTypeOfNode(p))
    ).str();
  DisplayAttributes(p); std::cout <<"\n";    
  bool first = true;
  for(auto& it : p.GetVarDecl()) {
    if(not first) std::cout << "\n";
    IncreaseIndent(); Indent(); it->Accept(*this); DecreaseIndent();
    first = false;
  }
  for(auto& it : p) {
    if(not first) std::cout << "\n";
    IncreaseIndent(); Indent(); it->Accept(*this); DecreaseIndent();
    first = false;
  }
  if(not first) std::cout << "\n";
}

void Dump::Visit(ProgInit const& p){

}

void Dump::Visit(ProgEnd const& p){
  DumpSymbolTable();
}

/////////////////////////////////////////////////////////////////////////////
void Dump::Visit(Block const& p) {
//   std::cout << "Stmts:\n";
//   bool first = true;
  for (auto& c : p.statements_){
//       if(not first)  std::cout << "\n";
      Indent(); c->Accept(*this);
      std::cout << "\n";
//       first = false;
  }
}

/////////////////////////////////////////////////////////////////////////////
void Dump::Visit(Literal const& p){
  std::cout << "[Lit] " ;
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
  bool first_elem = true;
  for(const auto& it : p.GetVarDeclVector()){
//     Indent();
    if(not first_elem) std::cout << "\n";
    it->Accept(*this); std::cout << " ";
    first_elem = false;
  }
}
void Dump::Visit(VarDecl const& p){
  std::cout << "[VDec] " << p.str();
}

void Dump::Visit(AssignStmt const& p){
  std::cout<< "[Assgn] "; DisplayAttributes(p); std::cout<<"\n";
  IncreaseIndent();
  Indent(); p.Lhs().Accept(*this); std::cout << "\n";
  Indent(); p.Rhs().Accept(*this);
  DecreaseIndent();
}

void Dump::Visit(Var& p){
  std::cout << "[Var] "<< p.str(); DisplayAttributes(p);
}

void Dump::Visit(RefOp const& p){
  std::cout << "[Refop] "<< p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.Rhs().Accept(*this); DecreaseIndent();
}

void Dump::Visit(DerefOp const& p){
  std::cout << "[Derop] "<< p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.Rhs().Accept(*this); DecreaseIndent();
}

void Dump::Visit(FuncCall& p){
  std::cout << "[Fcal] " << p.str(); DisplayAttributes(p);std::cout << "\n";

  //Dump receiver
  IncreaseIndent(); Indent(); p.Receiver().Accept(*this); DecreaseIndent();

  //Dump args
//   IncreaseIndent();
  for(const auto& it : p){
    std::cout << "\n";
    IncreaseIndent(); Indent(); it->Accept(*this); DecreaseIndent();

  }
//   DecreaseIndent();
}

void Dump::Visit(FuncRet& p){
  std::cout << "[Fret] " << p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.GetCall().Accept(*this); DecreaseIndent();
}

void Dump::Visit(ReturnStmt const& p){
  std::cout << "[Retst] "<< p.str(); DisplayAttributes(p);std::cout << "\n";
  IncreaseIndent(); Indent(); p.RetExpr().Accept(*this); DecreaseIndent();
}

void Dump::Visit(VarName const& p){
  std::cout << "[Vnam] " << p.str(); DisplayAttributes(p);
}

void Dump::Visit(DotOp const& p){
  std::cout << "[Dotop] " << p.str(); DisplayAttributes(p);std::cout << "\n";
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
    if(unit_.HasIsVarMember(p)) std::cout << " " << unit_.VarIsMemberStr(p);

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
