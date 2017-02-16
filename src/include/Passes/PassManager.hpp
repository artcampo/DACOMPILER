#pragma once
#include "CompilationUnit.hpp"
#include "TypeInference.hpp"

namespace Compiler{

class PassManager{
public:
  PassManager(CompilationUnit& unit):unit_(unit){};

  void Run(){
    TypeInference p1(unit_);

    p1.Run();
  };

protected:
  CompilationUnit&  unit_;
};


}//end namespace Compiler
