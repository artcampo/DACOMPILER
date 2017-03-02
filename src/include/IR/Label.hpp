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
  Label(const LabelId id, std::string name) : id_(id), name_(name){};
  virtual ~Label() = default;

  virtual PtrLabel Clone() const noexcept = 0;
  virtual std::string str() const noexcept = 0;
protected:
  LabelId id_;
  std::string name_;
};

struct LabelRT: public  Label{
  LabelRT(const LabelId id, std::string name) : Label(id, name){};
  LabelRT(const LabelRT& l) : Label(l.id_, l.name_){};

  ~LabelRT() = default;

  virtual std::string str() const noexcept{
    return name_;
  };
  virtual PtrLabel Clone() const noexcept{
    return std::unique_ptr<LabelRT>(new LabelRT(*this));
  };
protected:
};

struct LabelLT: public  Label{
  LabelLT(const LabelId id, std::string name) : Label(id, name){};
  LabelLT(const LabelLT& l) : Label(l.id_, l.name_){};

  ~LabelLT() = default;

  virtual std::string str() const noexcept{
    return name_;
  };

  virtual PtrLabel Clone() const noexcept{
    return std::unique_ptr<LabelLT>(new LabelLT(*this));
  };
protected:
};



}//end namespace IR
}//end namespace Compiler
