#include "scanner.h"

#include <fstream>
#include <iostream>
#include <cctype>

Scanner::~Scanner()
{
    for (auto token : _tokens){
        delete token;
    }
}

bool Scanner::isIdentifier(std::string token)
{
    std::regex identifierPattern("^[a-zA-Z][a-zA-Z0-9_]*$");
    return std::regex_match(token, identifierPattern);
}

bool Scanner::isFloatConstant(std::string token)
{
    std::regex identifierPattern("[+-]?([0-9]*[.])?[0-9]+$");
    return std::regex_match(token, identifierPattern);
}

bool Scanner::isIntConstant(std::string token)
{
    std::regex identifierPattern("[+-]?[0-9]+$");
    return std::regex_match(token, identifierPattern);
}

bool Scanner::isStringConstant(std::string token)
{
    return token.at(0) == '"' && token.at(token.length() - 1) == '"';
}

bool Scanner::isPunctuation(std::string token)
{
    for (std::string punctuation : _punctuations)
    {
        if (token == punctuation)
        {
            return true;
        }
    }
    return false;
}

bool Scanner::isRelop(std::string token)
{
    for (std::string relop : _relops)
    {
        if (token == relop)
        {
            return true;
        }
    }
    return false;
}

bool Scanner::isType(std::string token)
{
    for (std::string type : _types)
    {
        if (token == type)
        {
            return true;
        }
    }
    return false;
}

bool Scanner::isKeyword(std::string token)
{
    for (std::string keyword : _keywords)
    {
        bool tokenIsKeyword = token.compare(keyword) == 0;
        if (tokenIsKeyword)
        {
            return true;
        }
    }
    return false;
}

bool Scanner::isOperator(std::string token)
{
    for (std::string op : _operators)
    {
        bool tokenIsOperator = token.compare(op) == 0;
        if (tokenIsOperator)
        {
            return true;
        }
    }
    return false;
}

bool Scanner::isSignal(std::string token)
{
    return (token == "+" || token == "-");
}

bool Scanner::isAtribuition(std::string token)
{
    return (token == "=");
}

bool Scanner::shouldBreakToken(std::string token, std::string currentToken)
{
    if (currentToken.size() > 0) {
        bool currentTokenDefinesAString = currentToken.at(0) == '"';
        if (currentTokenDefinesAString) {
            return currentToken.size() > 1 && currentToken.at(currentToken.size() - 1) == '"';
        }
    }

    if (currentToken == "!" && token == "=") {
        return false;
    }

    return (isRelop(token) ||
           isPunctuation(token) ||
           isOperator(token) ||
           isSignal(token) ||
           isAtribuition(token));
}

Token* Scanner::_getToken(std::string token, int line, int column)
{
    if (isKeyword(token)) {
        return new Token(KEYWORD, token, line, column);
    } else if (isIntConstant(token)) {
        return new Token(INT_CONSTANT, token, line, column);
    } else if (isFloatConstant(token)) {
        return new Token(FLOAT_CONSTANT, token, line, column);
    } else if (isStringConstant(token)) {
        return new Token(STRING_CONSTANT, token, line, column);
    } else if (isType(token)) {
        return new Token(TYPE, token, line, column);
    } else if (isRelop(token)) {
        return new Token(RELOP, token, line, column);
    } else if (isOperator(token)) {
        return new Token(OPERATION, token, line, column);
    } else if (isIdentifier(token)) {
        return new Token(IDENT, token, line, column);
    } else if (isPunctuation(token)) {
        return new Token(PUNCTUATION, token, line, column);
    } else if (isSignal(token)) {
        return new Token(SIGNAL, token, line, column);
    } else if (isAtribuition(token)) {
        return new Token(ATRIBUITION, token, line, column);
    } else {
        return nullptr;
    }
}

std::vector<Token*> Scanner::scan(std::string file, SymbolTable* table)
{
    std::string currentToken = "";
    int column = 0;
    int line = 1;

    for (std::size_t i = 0; i < file.size(); ++i) {
        // For each character in file
        char ch = file[i];
        ++column;

        bool currentTokenDefinesAString = false;
        if (currentToken.size() > 0) {
            currentTokenDefinesAString = currentToken.at(0) == '"';
        }

        // Case char is new line character
        if (ch == '\n') {
            // If token is not empty
            if (!currentToken.empty()) {
                // Gets token
                Token* token = _getToken(currentToken, line, column);
                // If no token returned, throw error
                if (token == nullptr){
                    std::string error = "\033[31mUnmatched token:\033[0m '" + currentToken + "' at line " + std::to_string(line) + " column " + std::to_string(column-currentToken.length());
                    throw std::logic_error(error);
                }

                // Push to token list
                _tokens.push_back(token);

                // If token is identifier
                if (isIdentifier(currentToken)){
                    // Adds to symble table
                    table->addToken(currentToken, line, column-currentToken.length());
                }

                // Clear current token
                currentToken = "";
            }

            ++line;
            column = 0;
        // Case char is white space
        } else if (ch == ' ' || ch == '\t') {
            // If token is not empty
            if (!currentToken.empty() && !currentTokenDefinesAString) {
                // Gets token
                Token* token = _getToken(currentToken, line, column);

                // If no token returned, throw error
                if (token == nullptr){
                    std::string error = "\033[31mUnmatched token:\033[0m '" + currentToken + "' at line " + std::to_string(line) + " column " + std::to_string(column-currentToken.length());
                    throw std::logic_error(error);
                }

                // Push to token list
                _tokens.push_back(token);

                // If token is identifier
                if (isIdentifier(currentToken)){
                    // Adds to symble table
                    table->addToken(currentToken, line, column-currentToken.length());
                }

                // Clear current token
                currentToken = "";
            }

            if (currentTokenDefinesAString) {
                currentToken += ch;
            }
        // Case should break token
        } else if (shouldBreakToken(std::string("")+ch, currentToken)) {
            // If token is not empty
            if (!currentToken.empty()) {
                // Gets token
                Token* token = _getToken(currentToken, line, column);
                // If no token returned, throw error
                if (token == nullptr){
                    std::string error = "\033[31mUnmatched token:\033[0m '" + currentToken + "' at line " + std::to_string(line) + " column " + std::to_string(column-currentToken.length());
                    throw std::logic_error(error);
                }

                // Push to token list
                _tokens.push_back(token);

                // If token is identifier
                if (isIdentifier(currentToken)){
                    // Adds to symble table
                    table->addToken(currentToken, line, column-currentToken.length());
                }

                // Clear current token
                currentToken = "";
            }

            currentToken += ch;

            // Case char is relop
            if (isRelop(currentToken) || currentToken == "=" || currentToken == "!"){
                // Look Ahead
                char look_ahead = file[i+1];
                // If next char is '='
                if (look_ahead == '=') {
                    // Add to token
                    currentToken += look_ahead;
                    // Create token
                    Token* token = new Token(RELOP, currentToken, line, column);
                    _tokens.push_back(token);
                    // Adjusting file read position
                    i+=2;
                    column+=2;
                    // Clear current token
                    currentToken = "";
                }
            }
        // Case char is alfanum
        } else {
            // Case current token is not alfanum
            if (shouldBreakToken(currentToken, currentToken)) {
                // Gets token
                Token* token = _getToken(currentToken, line, column);
                // If no token returned, throw error
                if (token == nullptr){
                    std::string error = "\033[31mUnmatched token:\033[0m '" + currentToken + "' at line " + std::to_string(line) + " column " + std::to_string(column-currentToken.length());
                    throw std::logic_error(error);
                }

                // Push to token list
                _tokens.push_back(token);

                // Clear current token
                currentToken = "";
            }

            currentToken += ch;
        }

    }

    return _tokens;
}
