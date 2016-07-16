#pragma once
#include "CodeGeneratorLogger/Logger.h"

class FullLogger : public Logger{
  virtual void Logger(){};
  virtual void ~Logger(){};
};