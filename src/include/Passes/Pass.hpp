#pragma once
#include "CompilationUnit.hpp"

namespace Compiler{

class Pass{
public:
  Pass(CompilationUnit& unit):unit_(unit){};
  virtual void Run() = 0;

protected:
  CompilationUnit&  unit_;
};


}//end namespace Compiler
