#include "temporaryVariable.h"

std::string TemporaryVariable::newT() {
    std::string generatedT = "t" + std::to_string(_internalCounter);
    _internalCounter++;
    return generatedT;
}

std::string TemporaryVariable::currentT() {
    std::string generatedT = "t" + std::to_string(_internalCounter);
    return generatedT;
}
