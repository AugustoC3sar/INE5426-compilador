#include "temporaryVariable.h"

std::string TemporaryVariable::newT() {
    std::string generatedT = "t" + _internalCounter;
    _internalCounter++;
    return generatedT;
}
