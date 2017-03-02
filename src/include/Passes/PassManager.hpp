#pragma once
#include "CompilationUnit.hpp"
#include "TypeInference.hpp"
#include "CheckLvalRval.hpp"
#include "ComputeLocalVarOffsets.hpp"
#include "VarIsValueOrAddress.hpp"
#include <memory>

namespace Compiler{

class PassManager{
public:
  PassManager(CompilationUnit& unit)
    : unit_(unit)
    , check_lval_rval_(unit_)
    , var_is_val_or_addr_(unit_)
    , type_inference_(unit_)
    , compute_local_var_offsets_(unit_)
    , passes_ { &check_lval_rval_
              , &var_is_val_or_addr_
              , &type_inference_
              , &compute_local_var_offsets_}
  { defined_[CompUnitInfo::kAst] = true;};

  void Run(){
    for(auto& pass: passes_) Run(*pass);
  };

private:
  CompilationUnit&        unit_;
  CheckLvalRval           check_lval_rval_;
  VarIsValueOrAddress     var_is_val_or_addr_;
  TypeInference           type_inference_;
  ComputeLocalVarOffsets  compute_local_var_offsets_;

  std::vector<Pass*> passes_;
  std::map<CompUnitInfo, bool> defined_;

  void Run(Pass& p){
    for(const auto& info : p.Uses())
      if(not InfoIsDefined(info))
        unit_.Error(p.str() + " is missing input info: " + str(info));
    p.Run();
    for(const auto& info : p.Defines()) defined_[info] = true;
  }

  bool InfoIsDefined(const CompUnitInfo& info) const{
    auto it = defined_.find(info);
    if(it == defined_.end()) return false;
    return it->second;
  }

  std::string str(const CompUnitInfo& info){
    if(info == CompUnitInfo::kAst) return std::string("Ast");
    if(info == CompUnitInfo::kTypeOfNode) return std::string("Type of node");
    if(info == CompUnitInfo::kLnessRnessOfNode) return std::string("Lness/Rness of node");
    if(info == CompUnitInfo::kLocalVarOffsets ) return std::string("Offsets of local vars");
    return std::string("CompUnitInfo string missing");
  }

};


}//end namespace Compiler
