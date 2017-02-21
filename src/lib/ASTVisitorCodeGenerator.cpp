#include "ASTVisitorCodeGenerator.hpp"
#include "IRBuilder.hpp"
#include "Utils.hpp"
#include "ByteCode.hpp"


namespace Compiler{
namespace AST{

using namespace IRBuilder;
using VM::Reg;

void CodeGen::Visit(ProgBody const& p, const Node* successor){
//   std::cout << "P\n";
  p.GetProgInit()->Accept (*this, p.GetBlock());
  p.GetBlock()->Accept    (*this, p.GetProgEnd() );
  p.GetProgEnd()->Accept  (*this, nullptr );
}

void CodeGen::Visit(ProgInit const& p, const Node* successor){


}
void CodeGen::Visit(ProgEnd const& p, const Node* successor){
  EndOfProgram();
}

void CodeGen::BackPatch(const Node* n, const VM::Addr position){
//   std::cout << "**Backpatch try ["<< n->str()<< "]:" <<"("<<(void*)n<<")";
  std::map<const Node*, std::vector<VM::Addr>>::iterator it = back_patch_.find(n);
  if(it != back_patch_.end()){
    for(const auto& address : it->second){
      uint32_t& inst = byte_code_.GetInst(address);
//       std::cout << "Backpatch: "
//         << IRBuilder::PrintInstruction(inst)
//         << " with node: " << n->str() << "\n";
      IRBuilder::PatchJump(inst, position);
    }
    back_patch_.erase(it);
  }
//   else std::cout << " no entries";

//   std::cout << "\n";

//   PrintBackPatch();
}


void CodeGen::AddToBackPatch(const Node* n, const VM::Addr position){
//   std::cout << "**Backpatch insert ["<< n->str()<< "] has to patch:"
//             << IRBuilder::PrintInstruction(byte_code_.GetInst(position))
//             << "\n";
  //<<"("<<(void*)n<<")\n";
  back_patch_[n].push_back(position);
}

void CodeGen::PrintBackPatch() {
  std::cout << "-----------------------------------\n";
  for(auto e : back_patch_){
    std::cout << "** entry: ";
    std::cout << e.first->str()<<": ";
    for(const auto& address : e.second) std::cout << address<<" ";
    std::cout << "\n";
  }
  std::cout << "-----------------------------------\n";
}

/////////////////////////////////////////////////////////////////////////////
// Sucessor for an statement is either:
// - next statetement in current block
// - first node of block following enclosing block
void CodeGen::Visit(Block const& n, const Node* successor) {
//   std::cout << "B" << n.str()<< " with successor: " << successor->str() << "\n";
  BackPatch(&n, byte_code_.NextAddress());

  for (std::vector<Statement*>::const_iterator stmt = n.statements.cbegin();
        stmt != n.statements.cend(); ++stmt){
    const Node* actual_successor = successor;
    if(stmt != n.statements.cend() - 1 ) actual_successor = *(stmt + 1);

    BackPatch(*stmt, byte_code_.NextAddress());

    (*stmt)->Accept(*this, actual_successor);
  }
}

void CodeGen::Visit(AssignStmt const& p, const Node* successor){

}


void CodeGen::Visit(DeclStmt const& p, const Node* successor){
//   std::cout << "D"<< p.str()<<" with successor: " << successor->str() << "\n";
  p.GetVarDeclList()->Accept(*this, successor);
}

void CodeGen::Visit(VarDeclList const& p, const Node* successor){
  for(const auto d : p.GetVarDeclVector()) d->Accept(*this, successor);
}

void CodeGen::Visit(VarDecl const& p, const Node* successor){
  byte_code_.Append( NewVar(0) );
}

void CodeGen::Visit(IfStmt const& p, const Node* successor){
//   std::cout << "If"<< p.str()<< " with successor: " << successor->str() << "\n";
  p.GetCond()->Accept(*this, successor);

  const VM::Addr current_addr = byte_code_.NextAddress();
  const VM::Reg reg_src       = reg_of_Expr_[p.GetCond()];

  byte_code_.Append( JumpIfTrue (reg_src, 0) );
  byte_code_.Append( JumpIfFalse(reg_src, 0) );

  AddToBackPatch(p.GetThen(), current_addr + 0);

  if(p.HasElse()) AddToBackPatch(p.GetElse(), current_addr + 1);
  else            AddToBackPatch(successor,   current_addr + 1);


//   std::cout << "-Store backp to: " << p.GetThen()->str()<<"("<<(void*)p.GetThen()<<")"<<"\n";
//   std::cout << "-Store backp to: " << successor->str()<<"("<<(void*)successor<<")"<<"\n";

  p.GetThen()->Accept(*this, successor);

  //exit from then stmt
  byte_code_.Append( Jump(0) );
  AddToBackPatch(successor, byte_code_.NextAddress() - 1);

//   std::cout << "-Store backp to: " << successor->str()<<"\n";
//   std::cout <<"\n";
//   PrintBackPatch();
}

void CodeGen::Visit(WhileStmt const& p, const Node* successor){
  //
  const VM::Addr reentry_addr = byte_code_.NextAddress();
  p.GetCond()->Accept(*this, successor);
  const VM::Addr current_addr = byte_code_.NextAddress();
  const VM::Reg reg_src       = reg_of_Expr_[p.GetCond()];

  byte_code_.Append( JumpIfTrue (reg_src, 0) );
  byte_code_.Append( JumpIfFalse(reg_src, 0) );
  AddToBackPatch(p.GetBody(), current_addr + 0);
  AddToBackPatch(successor,   current_addr + 1);

  p.GetBody()->Accept(*this, successor);
  byte_code_.Append( JumpIfFalse(reg_src, reentry_addr) );
}

/////////////////////////////////////////////////////////////////////////////
void CodeGen::Visit(Literal const& n, const Node* successor){
  const uint32_t reg_assigned = reg_allocator_.freeRegister();
  reg_of_Expr_[&n]      = reg_assigned;
  byte_code_.stream.push_back( IRBuilder::Load(reg_assigned, n.Value()) );
}


/////////////////////////////////////////////////////////////////////////////
void CodeGen::Visit(BinaryOp const& n, const Node* successor){
  n.Lhs()->Accept(*this, successor);
  n.Rhs()->Accept(*this, successor);

  const VM::Reg reg_assigned = reg_allocator_.freeRegister();
  reg_of_Expr_[&n]      = reg_assigned;
  const VM::Reg reg_src1     = reg_of_Expr_[n.Lhs()];
  const VM::Reg reg_src2     = reg_of_Expr_[n.Rhs()];
  const VM::Reg op           = n.op;
  byte_code_.stream.push_back( IRBuilder::Arith(reg_src1, reg_src2,
                                                reg_assigned, op));
//   std::cout << "OP: " << op << "\n";
}

/////////////////////////////////////////////////////////////////////////////
void CodeGen::Print() const{
  VMUtils::print(byte_code_, true);
}

/////////////////////////////////////////////////////////////////////////////
void CodeGen::EndOfProgram(){
  byte_code_.stream.push_back( IRBuilder::Stop());
  Print();
}

}//end namespace AST
}//end namespace Compiler
