#pragma once
#include "IR/Label.hpp"
#include <map>

namespace Compiler{


class LabelManager{
public:
  LabelManager() : free_id_(0){
    labels_.push_back( std::move( std::make_unique<IR::LabelLT>(FreeId())));
    name_of_label_[0] = std::string("Main Data Segment");
  }

  const IR::Label& GetLabelMainDataSegment() const noexcept{
    return *(labels_.at(0));
  }

private:
  std::map<IR::LabelId, std::string> name_of_label_;
  std::vector<IR::PtrLabel> labels_;
  IR::LabelId   free_id_;

  const IR::LabelId FreeId() noexcept{ ++free_id_; return free_id_ - 1;}
};


}//end namespace Compiler
