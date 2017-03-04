#pragma once
#include <string>

namespace Compiler{

const static std::string kErr16("[error:16] Var used before declaration");

const static std::string kErr20("[err:20] while's condition is not a bool");
const static std::string kErr21("[err:21] if's condition is not a bool");
const static std::string kErr22("[err:22] left of assignment is not an Lval");
const static std::string kErr23("[err:23] referencing not an lvalue");
const static std::string kErr24("[err:24] dereferencing not an lvalue");
const static std::string kErr25("[err:25] dereferencing not a pointer");

const static std::string kErr26("[err:26] function declaration name missing");
const static std::string kErr27("[err:27] function declaration not followed by '('");
const static std::string kErr28("[err:28] function declaration's arguments not closed with ')'");
const static std::string kErr29("[err:29] function declaration's body not started with '{'");
const static std::string kErr30("[err:30] function declaration's body not closed with '}'");
const static std::string kErr31("[err:31] function body empty");
const static std::string kErr32("[err:32] function name already exists");
const static std::string kErr33("[err:33] function must start with return type");


}//end namespace Compiler
