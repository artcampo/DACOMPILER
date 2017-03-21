#pragma once
#include "Class.hpp"
#include "Scopes/ScopeId.hpp"
#include "AST/NodeClass.hpp"
#include <map>


namespace Compiler{

using AST::Class;
using AST::ScopeId;
using AST::HierarchicalScope;
using AST::ClassDef;

class ClassManager{
public:
  ClassManager() {

  }


  void EnterClassDefinition(const std::string& name){
//     NewClass(name, scope_owner_id);
  }
  void ExitClassDefinition(){}

  Class& GetClass(const std::string& name){ return *class_by_name_.at(name);}
  const Class& GetClass(const std::string& name) const { return *class_by_name_.at(name);}

protected:
  void NewClass(const std::string& name, const ScopeOwnerId scope_owner_id
    , const ScopeId scope_id
    , HierarchicalScope& scope
    , const IR::Label this_label
    , ClassDef& class_def){
    classes_.push_back( std::move(
      std::make_unique<Class>(name
                      , scope_owner_id
                      , scope_id
                      , scope
                      , this_label
                      , class_def)));
    class_by_name_[name] = classes_.back().get();


  }

private:
  std::vector<AST::PtrClass> classes_;
  std::map<std::string, Class*>  class_by_name_;


};


}//end namespace Compiler
