#ifndef SCANNER_H
#define SCANNER_H

#include "SymbolTable.h"
#include "token.h"

#include <string>
#include <vector>
#include <regex>

class Scanner
{
    private:
        // Buffer to optimize reading the input file
        char *buffer = new char[16];

        // Array to store keywords
        std::vector<std::string> _keywords = {
            "def", "print", "read", "return", "if", "else", "for", "new", "null", "break", "call"};
        
        // Array with types allowed on the language
        std::vector<std::string> _types = {"int", "float", "string"};

        // Array with relational operators
        std::vector<std::string> _relops = {"<", ">", "<=", ">=", "==", "!="};

        // Array with language operators
        std::vector<std::string> _operators = {"+", "-", "%", "="};

        // Array with ...
        std::vector<std::string> _punctuations = {",", ";", "(", ")", "[", "]", "{", "}"};

        // Tokens array
        std::vector<Token*> _tokens;


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
        bool isKeyword(std::string token);
        bool isOperator(std::string token);
        bool shouldBreakToken(char character);

    public:
        Scanner() = default;
        ~Scanner();

        std::vector<Token*> scan(std::string file, SymbolTable* table);
        Token* getNextToken();
    };

#endif