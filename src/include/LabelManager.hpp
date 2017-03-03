#pragma once
#include "IR/Label.hpp"
#include <map>

namespace Compiler{


class LabelManager{
public:
  LabelManager() : free_id_(0){
    name_of_label_[0] = std::string("Main");
    labels_.push_back(IR::Label::LabelLT(FreeId(), name_of_label_[0]));
  }

  const IR::Label& GetLabelMainDataSegment() const noexcept{
    return labels_.at(0);
  }

  std::string LabelStr(IR::LabelId id) const{
    return name_of_label_.at(id);
  }

private:
  std::map<IR::LabelId, std::string> name_of_label_;
  std::vector<IR::Label> labels_;
  IR::LabelId   free_id_;

  const IR::LabelId FreeId() noexcept{ ++free_id_; return free_id_ - 1;}
};


}//end namespace Compiler
