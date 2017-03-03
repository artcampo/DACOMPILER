#pragma once
#include <memory>
#include <string>
#include <cstddef>

namespace Compiler{
namespace IR{



using LabelId = size_t;
struct Label;
// using PtrLabel = std::unique_ptr<Label>;

struct Label{
  Label() = default;
  Label& operator= ( const Label &o ) = default;
  ~Label() = default;

  static Label LabelLT(const LabelId id, const std::string name){
    return Label(id, name, false);
  }

  /*
  static Label LabelRT(const LabelId id, const std::string name){
    return Label(id, name, true);
  }
  */

  bool  IsRunTime() const noexcept{ return is_rt_or_lt_;}
  bool  IsLinkTime() const noexcept{ return not is_rt_or_lt_;}


  std::string str() const noexcept{
    return name_;
  };
protected:
  LabelId     id_;
  std::string name_;
  bool        is_rt_or_lt_;

  Label(const LabelId id, const std::string name, const bool is_rt_or_lt_)
  : id_(id), name_(name){};
};




}//end namespace IR
}//end namespace Compiler
