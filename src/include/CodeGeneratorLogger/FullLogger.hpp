#pragma once
#include "CodeGeneratorLogger/Logger.hpp"

class FullLogger : public Logger{
  virtual void Logger(){};
  virtual void ~Logger(){};
};