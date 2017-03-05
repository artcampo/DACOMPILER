#pragma once
#include <memory>
#include <string>
#include <cstddef>

namespace Compiler{
namespace IR{



using LabelId = size_t;
struct Label;
using PtrLabel = std::unique_ptr<Label>;

struct Label{
  Label() = default;
  Label& operator= ( const Label &o ) = default;
  Label( const Label &o ) = default;
  ~Label() = default;
  /*
  Label& operator= ( const Label &o ){
    id_ = o.id_;
    name_ = o.name_;
    is_rt_or_lt_ = o.is_rt_or_lt_;
  }
   */

  static PtrLabel LabelLT(const LabelId id, const std::string name){
    return std::make_unique<Label>(id, name, false);
  }


  static PtrLabel LabelRT(const LabelId id, const std::string name){
    return std::make_unique<Label>(id, name, true);
  }

  const LabelId Id() const noexcept{ return id_;}
  bool  IsRunTime()  const noexcept{ return is_rt_or_lt_;}
  bool  IsLinkTime() const noexcept{ return not is_rt_or_lt_;}


  std::string str() const noexcept{
    return name_;
  };

  Label(const LabelId id, const std::string name, const bool is_rt_or_lt)
  : id_(id), name_(name), is_rt_or_lt_(is_rt_or_lt){};
private:
  LabelId     id_;
  std::string name_;
  bool        is_rt_or_lt_;


};




}//end namespace IR
}//end namespace Compiler
