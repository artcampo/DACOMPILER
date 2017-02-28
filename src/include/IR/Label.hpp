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
private:
  LabelId id_;
};

struct LabelRT: public  Label{
  LabelRT(const LabelId id) : Label(id){};

  ~LabelRT() = default;

  virtual std::string str() const noexcept{
    return std::string("LabelRT: ") + std::to_string(0);
  };
protected:
};

struct LabelLT: public  Label{
  LabelLT(const LabelId id) : Label(id){};

  ~LabelLT() = default;

  virtual std::string str() const noexcept{
    return std::string("LabelLT: ") + std::to_string(0);
  };
protected:
};



}//end namespace IR
}//end namespace Compiler
