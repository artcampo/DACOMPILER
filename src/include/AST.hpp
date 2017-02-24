#pragma once
#include "Node.hpp"
#include <memory>


namespace Compiler{
namespace AST{

struct Ast{
  Ast() : prog_(nullptr){}
//   Ast(AST::ProgBody* const prog) : prog_(std::make_unique<AST::ProgBody>(prog)){}

  std::unique_ptr<AST::ProgBody> prog_;
};

using PtrProgBody = std::unique_ptr<ProgBody>;

}//end namespace AST
}//end namespace Compiler
