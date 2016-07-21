#pragma once
#include "VM.hpp"

namespace CodeGenerator{

class RegisterAllocator{
public:
  RegisterAllocator() : next_register_(0){};
  
  int freeRegister(){
    using namespace VirtualMachineSpecs;
    int r = next_register_;
    next_register_ = (next_register_ + 1) % kNumberRegisters;
    return r;
  }
  
private:
  int next_register_;
};
  
};