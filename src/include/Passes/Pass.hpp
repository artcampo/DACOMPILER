#pragma once
#include "CompilationUnit.hpp"
#include <vector>
#include <string>

namespace Compiler{

// using CompilationUnitInfo::Info;

class Pass{
public:
  Pass(CompilationUnit& unit, const std::vector<CompUnitInfo>&& uses
    , const std::vector<CompUnitInfo>&& defines )
    : unit_(unit), uses_(uses), defines_(defines){};

  virtual void Run() = 0;
  virtual std::string str() const noexcept = 0;

  std::vector<CompUnitInfo>& Uses() noexcept{ return uses_;}
  std::vector<CompUnitInfo>& Defines() noexcept{ return defines_;}

  const std::vector<CompUnitInfo>& Uses() const noexcept{ return uses_;}
  const std::vector<CompUnitInfo>& Defines() const noexcept{ return defines_;}

protected:
  CompilationUnit&  unit_;
  std::vector<CompUnitInfo> uses_;
  std::vector<CompUnitInfo> defines_;
};


}//end namespace Compiler
