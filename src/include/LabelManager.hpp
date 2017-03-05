#pragma once
#include "IR/Label.hpp"
#include <map>

namespace Compiler{


class LabelManager{
public:
  LabelManager() : free_id_(0){
    IR::LabelId id = FreeId();
    name_of_label_[id] = std::string("MainDS");
    labels_.push_back(IR::Label::LabelLT(id, name_of_label_[0]));
  }

  const IR::Label& GetLabelMainLocals() const noexcept{
    return labels_.at(0);
  }

  std::string LabelStr(IR::LabelId id) const{
    return name_of_label_.at(id);
  }

  const IR::Label& NewFunctionEntryLabel(std::string function_name) noexcept{
    IR::LabelId id = FreeId();
    name_of_label_[id] = "entry_" + function_name;
    labels_.push_back(IR::Label::LabelLT(id, name_of_label_[id]));
    return labels_.at(id);
  }

  const IR::Label& NewFunctionARLabel(std::string function_name) noexcept{
    IR::LabelId id = FreeId();
    name_of_label_[id] = "arp_" + function_name;
    labels_.push_back(IR::Label::LabelRT(id, name_of_label_[id]));
    return labels_.at(id);
  }

private:
  std::map<IR::LabelId, std::string> name_of_label_;
  std::vector<IR::Label> labels_;
  IR::LabelId   free_id_;
  const IR::LabelId FreeId() noexcept{ ++free_id_; return free_id_ - 1;}
};


}//end namespace Compiler
