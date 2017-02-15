#pragma once
#include "Node.hpp"

namespace Compiler{
namespace AST{

struct Ast{
  Ast():block_(nullptr){}

  Block* block_;
};

}//end namespace AST
}//end namespace Compiler
