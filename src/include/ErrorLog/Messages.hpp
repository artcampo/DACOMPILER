#pragma once
#include <string>

namespace Compiler{

const static std::string kErr20("[err:20] while condition is not a bool");
const static std::string kErr21("[err:21] if condition is not a bool");
const static std::string kErr22("[err:22] left of assignment is not an Lval");
const static std::string kErr23("[err:23] referencing not an lvalue");
const static std::string kErr24("[err:24] dereferencing not an lvalue");
const static std::string kErr25("[err:25] dereferencing not a pointer");

}//end namespace Compiler
