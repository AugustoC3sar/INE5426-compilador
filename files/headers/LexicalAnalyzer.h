#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <string>
#include <vector>
#include <regex>
#include "SymbolTable.h"

enum TokenType
{
    PUNCTUATION,
    INT_CONSTANT,
    FLOAT_CONSTANT,
    STRING_CONSTANT,
    TYPE,
    IDENT,
    RESERVED_WORD,
    RELOP,
    OPERATION,
    END_OF_FILE,
    WAITING,
};

struct Token
{
    TokenType type;
    std::string value;
};

class LexicalAnalyzer
{
private:
    char *buffer = new char[16];
    std::vector<std::string> reservedWords = {
        "def", "print", "read", "return", "if", "else", "for", "new", "null", "break", "call"};
    std::vector<std::string> types = {"int", "float", "string"};
    std::vector<std::string> relops = {"<", ">", "<=", ">=", "==", "!="};
    std::vector<std::string> operators = {"+", "-", "%", "="};
    std::vector<std::string> punctuations = {",", ";", "(", ")", "[", "]", "{", "}"};
    std::vector<Token> tokens = {};
    bool parsedAllFile = false;
    const int BUFFER_COUNT = 16;
    long unsigned int currentTokenIterator = 0;

    bool isIdentifier(std::string token);
    bool isFloatConstant(std::string token);
    bool isIntConstant(std::string token);
    bool isStringConstant(std::string token);
    bool isPunctuation(std::string token);
    bool isRelop(std::string token);
    bool isType(std::string token);
    bool isReservedWord(std::string token);
    bool isOperator(std::string token);
    bool shouldBreakToken(char character);

public:
    LexicalAnalyzer() = default;

    SymbolTable parse(std::string filename);
    Token getNextToken();
};

#endif