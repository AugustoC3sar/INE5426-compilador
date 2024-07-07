#include "temporaryVariable.h"

std::string TemporaryVariable::newT() {
    _internalCounter++;
    std::string generatedT = "t" + std::to_string(_internalCounter);
    return generatedT;
}

std::string TemporaryVariable::currentT() {
    std::string generatedT = "t" + std::to_string(_internalCounter);
    return generatedT;
}
