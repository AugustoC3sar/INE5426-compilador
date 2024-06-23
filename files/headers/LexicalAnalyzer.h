#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <string>
#include <vector>
#include <regex>
#include "SymbolTable.h"

class LexicalAnalyzer
{
private:
    char *buffer = new char[16];
    std::vector<char> numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::vector<std::string> reservedWords = {
        "def", "int", "float", "string", "print",
        "read", "return", "if", "else", "for",
        "new", "null", "break", "call"};
    std::vector<std::string> operators = {
        "<", ">", "<=", ">=", "==", "!=",
        "+", "-", "*", "/", "%",
        "="};
    const int BUFFER_COUNT = 16;

    bool isIdentifier(std::string token);
    bool isNumber(std::string token);
    bool isReservedWord(std::string token);
    bool isOperator(std::string token);
    bool isString(std::string token);
    bool shouldBreakToken(char character);

public:
    LexicalAnalyzer() = default;

    SymbolTable parse(std::string filename);
};

#endif