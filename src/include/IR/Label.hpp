#pragma once
#include <memory>
#include <string>
#include <cstddef>

namespace Compiler{
namespace IR{



using LabelId = size_t;
struct Label;
struct LabelRT;
struct LabelLT;
using PtrLabel = std::unique_ptr<Label>;

struct Label{
  Label(const LabelId id) : id_(id){};
  virtual ~Label() = default;

  virtual std::string str() const noexcept = 0;
  virtual PtrLabel Clone() const noexcept = 0;
protected:
  LabelId id_;
};

struct LabelRT: public  Label{
  LabelRT(const LabelId id) : Label(id){};
  LabelRT(const LabelRT& l) : Label(l.id_){};

  ~LabelRT() = default;

  virtual std::string str() const noexcept{
    return std::string("LabelRT: ") + std::to_string(0);
  };
  virtual PtrLabel Clone() const noexcept{
    return std::unique_ptr<LabelRT>(new LabelRT(*this));
  };
protected:
};

struct LabelLT: public  Label{
  LabelLT(const LabelId id) : Label(id){};
  LabelLT(const LabelLT& l) : Label(l.id_){};

  ~LabelLT() = default;

  virtual std::string str() const noexcept{
    return std::string("LabelLT: ") + std::to_string(0);
  };

  virtual PtrLabel Clone() const noexcept{
    return std::unique_ptr<LabelLT>(new LabelLT(*this));
  };
protected:
};



}//end namespace IR
}//end namespace Compiler
