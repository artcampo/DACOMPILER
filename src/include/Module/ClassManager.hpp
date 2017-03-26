#pragma once
#include "Class.hpp"
#include "Scopes/ScopeId.hpp"
#include "AST/NodeClass.hpp"
#include "Types.hpp"
#include "Types/ClassType.hpp"
#include "Module/ScopeManager.hpp"
#include "Module/TypeTable.hpp"
#include "Module/LabelManager.hpp"
#include "Module/FunctionManager.hpp"
#include <map>


namespace Compiler{

using AST::Class;
using AST::ScopeId;
using AST::HierarchicalScope;
using AST::ClassDef;

class ClassManager{
public:
  ClassManager(ScopeManager* scope_manager, TypeTable* type_table
    , LabelManager* label_manager, FunctionManager* function_manager)
    : scope_manager_(*scope_manager), type_table_(*type_table)
      , label_manager_(*label_manager), function_manager_(*function_manager){}

  void EnterClassDefinition(const std::string& name){
//     NewClass(name, scope_owner_id);
  }
  void ExitClassDefinition(){}

  Class& GetClass(const std::string& name){ return *class_by_name_.at(name);}
  const Class& GetClass(const std::string& name) const { return *class_by_name_.at(name);}

  const Class& GetClass(const ClassType& type) const { return *class_by_typeid_.at(type.GetTypeId());}
  Class& GetClass(ClassType& type) { return *class_by_typeid_.at(type.GetTypeId());}

  const ScopeId NewClassDecl(std::string& class_name
    , std::vector<ClassType*>& parent_types){
    std::vector<HierarchicalScope*> parent_scopes;
    std::vector<Class*> parent_classes;
    for(auto& parent : parent_types) {
      parent_classes.push_back( &GetClass(*parent) );
      parent_scopes.push_back ( &GetClass(*parent).GetHScope());
    }
    const ScopeOwnerId owner_id = scope_manager_.NewScopeOwner();
    const ScopeId id = scope_manager_.NewHierarchicalScope(class_name, owner_id
      , type_table_.GetClassType(class_name), parent_scopes);
    class_decl_owner_id_[class_name] = owner_id;
    class_parents_[class_name] = parent_classes;
    return id;
  }  
  
  void NewClass(std::string& class_name, const ScopeId hscope_id
    , ClassDef& class_def){
//     std::cout << "Creating class with " << class_parents_[class_name].size()<< " parents\n";
    classes_.push_back( std::move(
      std::make_unique<Class>(class_name
                      , class_decl_owner_id_[class_name]
                      , hscope_id
                      , dynamic_cast<HierarchicalScope&>(*scope_manager_.GetScope(hscope_id))
                      , label_manager_.NewClassThisLabel(class_name)
                      , class_parents_[class_name]
                      , class_def
                      , &function_manager_)));
    Class* c = classes_.back().get();
    const ClassType& type = type_table_.GetClassType(class_name);
    class_by_name_[class_name] = c;
    class_by_typeid_[type.GetTypeId()] = c;
    type_table_.SetClassTypeSize(class_name, c->Size());
  }  
  
protected:

private:
  ScopeManager&                 scope_manager_;
  TypeTable&                    type_table_;
  LabelManager&                 label_manager_;
  FunctionManager&              function_manager_;
  
  std::vector<AST::PtrClass>    classes_;
  std::map<std::string, Class*> class_by_name_;
  std::map<TypeId, Class*>      class_by_typeid_;

  //TODO: needed?
  std::map<std::string, ScopeOwnerId> class_decl_owner_id_;
  std::map<std::string, std::vector<Class*>> class_parents_;
  

};


}//end namespace Compiler
