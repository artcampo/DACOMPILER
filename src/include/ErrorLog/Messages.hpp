#pragma once
#include <string>

namespace Compiler{

const static std::string kErr4("[err:4] Expecting semicolon after Expr.");
const static std::string kErr14("[err:14] Expecting rpar after expression.");
const static std::string kErr15("[err:15] Symbol already declared.");
const static std::string kErr16("[error:16] Var used before declaration");



const static std::string kErr18("[err:18] Incompatible types in assignment: ");
const static std::string kErr19("[err:19] Variable declarations must be separated with comma.");

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
const static std::string kErr34("[err:34] parameters must be separated with comma");
const static std::string kErr35("[err:35] Expecting rpar closing function call");
const static std::string kErr36("[err:36] Argument not containing an expression");
const static std::string kErr37("[err:37] Function call refers to non declared function");
const static std::string kErr38("[err:38] Function call with a non-function name");
const static std::string kErr39("[err:39] Function call with less arguments than expected");
const static std::string kErr40("[err:40] Function call with more arguments than expected (extra arguments will be discarded)");
const static std::string kErr41("[err:41] Argument type conflict: ");
const static std::string kErr42("[err:42] ");
const static std::string kErr43("[err:43] Missing semicolon after return statement. ");
const static std::string kErr44("[err:44] Return statement not inside function definition. ");
const static std::string kErr45("[err:45] Return's expression doesn not match function return type: ");
const static std::string kErr46("[err:46] function call used before declaration");

const static std::string kErr80("[err:80] class declaration name missing");
const static std::string kErr81("[err:81] class declaration not started with '{'");
const static std::string kErr82("[err:82] class declaration not closed with '}'");
const static std::string kErr83("[err:83] class declaration must start with 'class'");
const static std::string kErr84("[err:84] class name already exists");
const static std::string kErr85("[err:85] class instance used before declaration");
const static std::string kErr86("[err:86] class member name symbol missing");
const static std::string kErr87("[err:87] class member should be either var decl or function, but it's missing either ';' or '('");
const static std::string kErr88("[err:88] expecting class member");
const static std::string kErr89("[err:89] symbol is not a class (of dot op), instead it is ");
const static std::string kErr90("[err:90] rhs of dot must be a name");
const static std::string kErr91("[err:91] invalid member variable access ");
const static std::string kErr92("[err:92] type in inheritance list is not class, instead is ");
const static std::string kErr93("[err:93] inheritance list has to start with ':' ");
const static std::string kErr94("[err:94] inheritance list has to be separated with ',' ");


const static std::string kErrUn1("[err:x1] name not followed by valid token");

}//end namespace Compiler
