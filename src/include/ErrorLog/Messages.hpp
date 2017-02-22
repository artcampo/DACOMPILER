#pragma once
#include <string>

namespace Compiler{
/*
class enum ErrorMessages : std::string{
  kErr20
};
*/
const static std::string kErr20("[err:] while condition is not a bool");
const static std::string kErr21("[err:] if condition is not a bool");

/*
std::string str(const ErrorMessages){
  if() return std::string("e1");
}
*/

}//end namespace Compiler
