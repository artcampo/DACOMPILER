#pragma once
#include <cstddef>


namespace Compiler{
namespace AST{



  
class TypeId {
public:
  TypeId(const size_t id): id_(id){}
  
  size_t Id() const noexcept {return id_;};
private:
  size_t id_;
};


}//end namespace AST
}//end namespace Compiler
