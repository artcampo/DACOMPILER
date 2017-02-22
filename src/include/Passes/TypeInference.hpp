#pragma once
#include "Passes/Pass.hpp"
#include "ASTVisitor.hpp"
#include "CompilationUnit.hpp"
#include "Types.hpp"
#include "ErrorLog/Messages.hpp"

namespace Compiler{

using namespace AST;

class ASTVisitorTypeInference : public ASTVisitor{
public:

  ASTVisitorTypeInference(CompilationUnit& unit): unit_(unit){};

  virtual void Visit(ProgBody const& p){
    p.GetProgInit()->Accept(*this);
    p.GetBlock()->Accept(*this);
    p.GetProgEnd()->Accept(*this);
  }

  virtual void Visit(ProgInit const& p){};
  virtual void Visit(ProgEnd const& p){};

  virtual void Visit(Block const& p){
    for (auto c : p.statements) c->Accept(*this);
  }
  virtual void Visit(IfStmt const& p){
    p.GetCond()->Accept(*this);
    p.GetThen()->Accept(*this);
    if(p.HasElse()) p.GetElse()->Accept(*this);

    if(not unit_.GetTypeId(p.GetCond()).IsBool())
      unit_.Error(kErr21, p.GetCond()->GetLocus());
  }

  virtual void Visit(WhileStmt const& p){
    p.GetCond()->Accept(*this);
    p.GetBody()->Accept(*this);

    if(not unit_.GetTypeId(p.GetCond()).IsBool())
      unit_.Error(kErr20, p.GetCond()->GetLocus());
  }

  virtual void Visit(BinaryOp const& p){
    p.Lhs()->Accept(*this);
    p.Rhs()->Accept(*this);
    if(unit_.GetTypeId(p.Lhs()) == unit_.GetTypeId(p.Rhs()))
      unit_.RecordType(&p, unit_.GetTypeId(p.Lhs()));
    else
      unit_.Error("[err:17] Incompatible types in op", p.GetLocus());
  }
  virtual void Visit(AssignStmt const& p){
    p.Lhs()->Accept(*this);
    p.Rhs()->Accept(*this);
    if(unit_.GetTypeId(p.Lhs()) == unit_.GetTypeId(p.Rhs()))
      unit_.RecordType(&p, unit_.GetTypeId(p.Lhs()));
    else
      unit_.Error("[err:18] Incompatible types in assignment", p.GetLocus());
  }

  virtual void Visit(Literal const& p){unit_.RecordType(&p, p.GetTypeId());}
  virtual void Visit(Var const& p)    {unit_.RecordType(&p, p.GetTypeId());}
  virtual void Visit(DeclStmt const& p){}
  virtual void Visit(VarDeclList const& p){}
  virtual void Visit(VarDecl const& p){}

private:
  CompilationUnit&  unit_;
};

class TypeInference : public Pass{
public:
  TypeInference(CompilationUnit& unit)
    : Pass(unit, {CompUnitInfo::kAst}, {CompUnitInfo::kTypeOfNode}) {};

// std::vector<CompUnitInfo>()
  virtual void Run(){
    if(unit_.ValidAst()){
      ASTVisitorTypeInference v(unit_);
      v.Visit(*unit_.GetAstProg());
    }
  };

  virtual std::string str() const noexcept{
    return std::string("Type inference");
  };
protected:

};


}//end namespace Compiler
