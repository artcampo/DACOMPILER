#pragma once
#include "AST.hpp"
#include "LexicalScope.hpp"

namespace Compiler{

using AST::Ast;
using AST::LexicalScope;

class CompilationUnit {
public:

  CompilationUnit(): ast_(), scope_(nullptr){}

  Ast            ast_;
  LexicalScope*  scope_;
};


}//end namespace Compiler
