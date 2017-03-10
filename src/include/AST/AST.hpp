#pragma once
#include <memory>

namespace Compiler{
namespace AST{

class ProgBody;

struct Ast{
  Ast() : prog_(nullptr){}
//   Ast(AST::ProgBody* const prog) : prog_(std::make_unique<AST::ProgBody>(prog)){}

  std::unique_ptr<AST::ProgBody> prog_;
};


namespace Ptrs{
using PtrProgBody = std::unique_ptr<ProgBody>;
}//end namespace Ptrs

}//end namespace AST
}//end namespace Compiler
