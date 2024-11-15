#ifndef SCANNER_H
#define SCANNER_H

#include "symbolTable.h"
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
        std::vector<std::string> _operators = {"/", "%", "*"};

        // Array with ...
        std::vector<std::string> _punctuations = {",", ";", "(", ")", "[", "]", "{", "}"};

        // Tokens array
        std::vector<Token*> _tokens;

        // Definitions of methods to recognize token's type
        bool isIdentifier(std::string token);
        bool isFloatConstant(std::string token);
        bool isIntConstant(std::string token);
        bool isStringConstant(std::string token);
        bool isPunctuation(std::string token);
        bool isRelop(std::string token);
        bool isType(std::string token);
        bool isKeyword(std::string token);
        bool isOperator(std::string token);
        bool isSignal(std::string token);
        bool isAtribuition(std::string token);
        bool shouldBreakToken(std::string token, std::string currentToken);

        /**
         * Abstraction of the process of token's type identification and creation of token object
         * 
         * @param token: token's lexical value
         * @param line: line of token's occurrence
         * @param column: column of token's occurrence
         * @return token object created
         */
        Token* _getToken(std::string token, unsigned int line, unsigned int column);

    public:
        /**
         * Constructor
         */
        Scanner() {};

        /**
         * Destructor
         */
        ~Scanner();

        /**
         * Scanner main method. Iterate over file reading each character and identifying tokens.
         * 
         * @param file: the whole file converted to a string
         * @param table: Symbol table from the compiler
         * @return list of identified tokens
         */
        std::vector<Token*> scan(std::string file, SymbolTable* table);
    };

#endif