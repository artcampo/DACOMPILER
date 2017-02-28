#include "IR/IRGenerator.hpp"


namespace Compiler{
namespace AST{

void IRGenerator::Visit(ProgBody const& p, const Node* successor){
//   std::cout << "P\n";
  p.GetProgInit().Accept (*this, &p.GetBlock());
  p.GetBlock().Accept    (*this, &p.GetProgEnd() );
  p.GetProgEnd().Accept  (*this, nullptr );
}

void IRGenerator::Visit(ProgInit const& p, const Node* successor){


}
void IRGenerator::Visit(ProgEnd const& p, const Node* successor){
}


/////////////////////////////////////////////////////////////////////////////
// Sucessor for an statement is either:
// - next statetement in current block
// - first node of block following enclosing block
void IRGenerator::Visit(Block const& n, const Node* successor) {

//   std::cout << "B" << n.str()<< " with successor: " << successor->str() << "\n";
  BackPatch(n, stream_.NextAddress());

  for (std::vector<PtrStatement>::const_iterator stmt = n.statements_.cbegin();
        stmt != n.statements_.cend(); ++stmt){
    const Node* actual_successor = successor;
    if(stmt != n.statements_.cend() - 1 )
      actual_successor = (stmt + 1)->get();

    BackPatch(**stmt, stream_.NextAddress());

    (*stmt)->Accept(*this, actual_successor);
  }

}

void IRGenerator::Visit(AssignStmt const& p, const Node* successor){
  p.Rhs().Accept(*this, successor);
  p.Lhs().Accept(*this, successor);
}


void IRGenerator::Visit(DeclStmt const& p, const Node* successor){
//   std::cout << "D"<< p.str()<<" with successor: " << successor->str() << "\n";
  p.GetVarDeclList().Accept(*this, successor);
}

void IRGenerator::Visit(VarDeclList const& p, const Node* successor){
  for(const auto& d : p.GetVarDeclVector()) d->Accept(*this, successor);
}

void IRGenerator::Visit(VarDecl const& p, const Node* successor){
//   stream_.Append( NewVar(0) );
}

void IRGenerator::Visit(IfStmt const& p, const Node* successor){

//   std::cout << "If"<< p.str()<< " with successor: " << successor->str() << "\n";

  p.GetCond().Accept(*this, successor);

  const IR::Addr current_addr = stream_.NextAddress();
  const IR::Reg  reg_src       = reg_of_expr_[&p.GetCond()];

  stream_.AppendJumpIfTrue (reg_src);
  stream_.AppendJumpIfFalse(reg_src);

  AddToBackPatch(p.GetThen(), current_addr + 0);

  if(p.HasElse()) AddToBackPatch(p.GetElse(), current_addr + 1);
  else            AddToBackPatch(*successor,  current_addr + 1);


//   std::cout << "-Store backp to: " << p.GetThen().str()<<"("<<(void*)p.GetThen()<<")"<<"\n";
//   std::cout << "-Store backp to: " << successor->str()<<"("<<(void*)successor<<")"<<"\n";

  p.GetThen().Accept(*this, successor);

  //exit from then stmt
  stream_.AppendJumpInconditional();
  AddToBackPatch(*successor, stream_.NextAddress() - 1);

//   std::cout << "-Store backp to: " << successor->str()<<"\n";
//   std::cout <<"\n";
//   PrintBackPatch();

}

void IRGenerator::Visit(WhileStmt const& p, const Node* successor){

  //
  const IR::Addr reentry_addr = stream_.NextAddress();
  p.GetCond().Accept(*this, successor);
  const IR::Addr current_addr = stream_.NextAddress();
  const IR::Reg reg_src       = reg_of_expr_[&p.GetCond()];

  stream_.AppendJumpIfTrue(reg_src);
  stream_.AppendJumpIfFalse(reg_src);
  AddToBackPatch(p.GetBody(), current_addr + 0);
  AddToBackPatch(*successor,   current_addr + 1);

  p.GetBody().Accept(*this, successor);
  stream_.AppendJumpIfFalse(reg_src, reentry_addr);

}

/////////////////////////////////////////////////////////////////////////////
void IRGenerator::Visit(Literal const& n, const Node* successor){
  const IR::Reg r  = stream_.AppendLoadI( n.Value() );
  reg_of_expr_[&n] = r;
}


/////////////////////////////////////////////////////////////////////////////
void IRGenerator::Visit(BinaryOp const& n, const Node* successor){

  n.Lhs().Accept(*this, successor);
  n.Rhs().Accept(*this, successor);

  const IR::Reg reg_src1 = reg_of_expr_[&n.Lhs()];
  const IR::Reg reg_src2 = reg_of_expr_[&n.Rhs()];
  const IR::ArithType op = IR::ArithType(n.op);
  const IR::Reg r  = stream_.AppendArith(reg_src1, reg_src2, op);
  reg_of_expr_[&n]      = r;
//   std::cout << "OP: " << op << "\n";

}

void IRGenerator::Visit(RefOp const& p, const Node* successor){}
void IRGenerator::Visit(DerefOp const& p, const Node* successor){}
void IRGenerator::Visit(Var const& p, const Node* successor){}

/////////////////////////////////////////////////////////////////////////////
void IRGenerator::Print() const noexcept{
  stream_.Print();
}

/////////////////////////////////////////////////////////////////////////////
void IRGenerator::EndOfProgram(){
//   stream_.stream.push_back( IRBuilder::Stop());
  Print();
}



void IRGenerator::BackPatch(const Node& n, const IR::Addr position){
//   std::cout << "**Backpatch try ["<< n->str()<< "]:" <<"("<<(void*)n<<")";
  std::map<const Node*, std::vector<IR::Addr>>::iterator it = back_patch_.find(&n);
  if(it != back_patch_.end()){
    for(const auto& address : it->second){
      IR::Jump& inst = dynamic_cast<IR::Jump&>(stream_.GetInst(address));
//       std::cout << "Backpatch: "
//         << IRBuilder::PrintInstruction(inst)
//         << " with node: " << n->str() << "\n";
      inst.PatchJump(position);
    }
    back_patch_.erase(it);
  }
//   else std::cout << " no entries";

//   std::cout << "\n";

//   PrintBackPatch();
}


void IRGenerator::AddToBackPatch(const Node& n, const IR::Addr position){
//   std::cout << "**Backpatch insert ["<< n->str()<< "] has to patch:"
//             << IRBuilder::PrintInstruction(stream_.GetInst(position))
//             << "\n";
  //<<"("<<(void*)n<<")\n";
  back_patch_[&n].push_back(position);
}

void IRGenerator::PrintBackPatch() {
  std::cout << "-----------------------------------\n";
  for(auto e : back_patch_){
    std::cout << "** entry: ";
    std::cout << e.first->str()<<": ";
    for(const auto& address : e.second) std::cout << address<<" ";
    std::cout << "\n";
  }
  std::cout << "-----------------------------------\n";
}

}//end namespace AST
}//end namespace Compiler
