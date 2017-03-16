#pragma once
#include <cstddef>
#include <vector>
#include <iterator>
#include <iostream>
#include "Locus.hpp"

namespace Compiler{


class ErrorLog{
public:
  ErrorLog(): num_errors_(0){}
  void SetFileData(std::vector<char>* file_data){ file_data_= file_data;};

//ErrorLog(std::vector<char>& file_data) : file_data_(file_data){}

void Error(const std::string& message, const Locus& locus){
  ++num_errors_;
  std::cout << message << " at: \"";
  std::vector<char>::const_iterator current_position = locus.Iterator();
  {
    std::vector<char>::const_iterator start_of_error = current_position;
    for(int i = 0; i < num_characters_to_display_before_error_
                  and start_of_error != file_data_->cbegin(); ++i)
      --start_of_error;

    while(start_of_error != current_position){
      std::cout << *start_of_error;
      ++start_of_error;
    }
  }
  std::cout << "\" -> \"";
  //Go forward K chars
  {
    std::vector<char>::const_iterator start_of_error = current_position;
    for(int i = 0; i < num_characters_to_display_after_error_ and
        start_of_error != file_data_->cend(); ++start_of_error)
      std::cout << *start_of_error;
  }

  std::cout << "\"" << std::endl;
}

void Error(const std::string& message){
  ++num_errors_;
  std::cout << message << std::endl;
}

void FatalError(const std::string& message){
  ++num_errors_;
  std::cout << "FATAL: " << message << std::endl;
}

int NumErrors() const noexcept {return num_errors_;}

private:
  std::vector<char>* file_data_;

  const static int num_characters_to_display_before_error_ = 10;
  const static int num_characters_to_display_after_error_  = 10;
  int               num_errors_;
};

}//end namespace Compiler
