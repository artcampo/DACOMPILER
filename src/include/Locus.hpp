#pragma once
#include <vector>
#include <iterator>


namespace Compiler{

class Locus{
public:
  Locus(){};
  Locus(const std::vector<char>::const_iterator pos): pos_(pos){}


  std::vector<char>::const_iterator Iterator() const { return pos_;}

private:
  const std::vector<char>::const_iterator pos_;
};

}//end namespace Compiler
