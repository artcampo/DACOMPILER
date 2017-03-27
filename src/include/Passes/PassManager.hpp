#pragma once
#include "CompilationUnit.hpp"
#include "TypeInference.hpp"
#include "TypeCheck.hpp"
#include "CheckLvalRval.hpp"
#include "ComputeLocalVarOffsets.hpp"
#include "VarIsValueOrAddress.hpp"
#include "VarIsReadOrWrite.hpp"
#include "ResolveMemberTypes.hpp"
#include "DeferredNodesCreation.hpp"
#include "VarIsMember.hpp"
#include "LexicalScopeOfNode.hpp"

#include <memory>

namespace Compiler{

//AST comes from parsing in kAstIncomplete1 form

class PassManager{
public:
  PassManager(CompilationUnit& unit)
    : unit_(unit)
    , check_lval_rval_(unit_)
    , var_is_read_or_write_(unit_)
    , var_is_val_or_addr_(unit_)
    , type_inference_(unit_)
    , type_check_(unit_)
    , compute_local_var_offsets_(unit_)
    , resolve_member_types_(unit_)
    , deferred_nodes_creation_(unit_, type_inference_.v_)
    , var_is_member_(unit_)
    , lscope_of_node_(unit_)
    , passes_ { &resolve_member_types_
              , &deferred_nodes_creation_
              , &check_lval_rval_
              , &var_is_read_or_write_
              , &var_is_val_or_addr_
              , &lscope_of_node_
              , &type_inference_
              , &type_check_
              , &var_is_member_
              , &compute_local_var_offsets_}
  { defined_[CompUnitInfo::kAstIncomplete1] = true;};

  void Run(){
    for(auto& pass: passes_){
      Run(*pass);
      //Any error in the semantic phase is critical
      if(unit_.HasErrors())break;
    }
  };

private:
  CompilationUnit&        unit_;
  CheckLvalRval           check_lval_rval_;
  VarIsReadOrWrite        var_is_read_or_write_;
  VarIsValueOrAddress     var_is_val_or_addr_;
  TypeInference           type_inference_;
  TypeCheck               type_check_;
  ComputeLocalVarOffsets  compute_local_var_offsets_;
  ResolveMemberTypes      resolve_member_types_;
  DeferredNodesCreation   deferred_nodes_creation_;
  VarIsMember             var_is_member_;
  LexicalScopeOfNode      lscope_of_node_;

  std::vector<Pass*>            passes_;
  std::map<CompUnitInfo, bool>  defined_;

  void Run(Pass& p){
    for(const auto& info : p.Uses())
      if(not InfoIsDefined(info))
        unit_.Error(p.str() + " is missing input info: " + str(info));
    p.Run();
//     std::cout << "Run pass: " << p.str() << "\n";
    if(unit_.HasErrors()) std::cout << p.str() << " failed. \n";
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
