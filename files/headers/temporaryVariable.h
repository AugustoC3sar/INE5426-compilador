#ifndef TEMPORARY_VARIABLE_H
#define TEMPORARY_VARIABLE_H

#include <string>

class TemporaryVariable {
private:
  int _internalCounter = 0;

public:
  std::string newT();
  std::string currentT();
};

#endif
