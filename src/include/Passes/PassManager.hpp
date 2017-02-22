#pragma once
#include "CompilationUnit.hpp"
#include "TypeInference.hpp"
#include <memory>

namespace Compiler{

class PassManager{
public:
  PassManager(CompilationUnit& unit)
    : unit_(unit), type_inference_(unit_), passes_{&type_inference_}{
      defined_[CompUnitInfo::kAst] = true;
    };

  void Run(){
    for(auto& pass: passes_){
      Run(*pass);
    }
  };

protected:
  CompilationUnit&  unit_;

private:
  std::map<CompUnitInfo, bool> defined_;
  TypeInference type_inference_;
  std::vector<Pass*> passes_;

  void Run(Pass& p){
    for(const auto& info : p.Uses())
      if(not InfoIsDefined(info))
        unit_.Error(p.str() + " is missing input info: " + str(info));
    p.Run();
    for(const auto& info : p.Defines())
      defined_[info] = true;
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
    return std::string("CompUnitInfo string missing");
  }

};


}//end namespace Compiler
