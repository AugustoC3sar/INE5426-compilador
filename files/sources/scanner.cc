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
    for (std::string reservedWord : _keywords)
    {
        bool tokenIsReservedWord = token.compare(reservedWord) == 0;
        if (tokenIsReservedWord)
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

bool Scanner::shouldBreakToken(char character)
{
    return isspace(character) ||
           character == '(' ||
           character == ')' ||
           character == '{' ||
           character == '}' ||
           character == ';' ||
           character == ',' ||
           character == '[' ||
           character == ']';
}

std::vector<Token*> Scanner::scan(std::string file, SymbolTable* table)
{
    std::string currentToken;
    int column = 0;
    int line = 1;

    for (size_t i = 0; i < file.size(); ++i) {
        char c = file[i];
        ++column;
        if (shouldBreakToken(c)) {
            if (isPunctuation(std::string(1, c))) {
                if (currentToken.empty()) {
                    currentToken += c;
                } else {
                    i--;
                }
            }

            if (!currentToken.empty()) {
                if (isKeyword(currentToken)) {
                    _tokens.push_back(new Token(KEYWORD, line, column-currentToken.length(), currentToken));
                } else if (isIntConstant(currentToken)) {
                    _tokens.push_back(new Token(INT_CONSTANT, line, column-currentToken.length(), currentToken));
                } else if (isFloatConstant(currentToken)) {
                    _tokens.push_back(new Token(FLOAT_CONSTANT, line, column-currentToken.length(), currentToken));
                } else if (isStringConstant(currentToken)) {
                    _tokens.push_back(new Token(STRING_CONSTANT, line, column-currentToken.length(), currentToken));
                } else if (isType(currentToken)) {
                    _tokens.push_back(new Token(TYPE, line, column-currentToken.length(), currentToken));
                } else if (isRelop(currentToken)) {
                    _tokens.push_back(new Token(RELOP, line, column-currentToken.length(), currentToken));
                } else if (isOperator(currentToken)) {
                    _tokens.push_back(new Token(OPERATION, line, column-currentToken.length(), currentToken));
                } else if (isIdentifier(currentToken)) {
                    Token* token = new Token(IDENT, line, column-currentToken.length(), currentToken);
                    _tokens.push_back(token);
                    table->addToken(token);
                } else if (isPunctuation(currentToken)) {
                    _tokens.push_back(new Token(PUNCTUATION, line, column-currentToken.length(), currentToken));
                } else {
                    std::string error = "\033[31mUnmatched token:\033[0m " + currentToken;
                    throw std::logic_error(error);
                }
                currentToken.clear();
            }
        } else if (isOperator(std::string(1, c)) || isRelop(std::string(1, c))) {
            if (!currentToken.empty()) {
                if (isKeyword(currentToken)) {
                    _tokens.push_back(new Token(KEYWORD, line, column-currentToken.length(), currentToken));
                } else if (isIntConstant(currentToken)) {
                    _tokens.push_back(new Token(INT_CONSTANT, line, column-currentToken.length(), currentToken));
                } else if (isFloatConstant(currentToken)) {
                    _tokens.push_back(new Token(FLOAT_CONSTANT, line, column-currentToken.length(), currentToken));
                } else if (isStringConstant(currentToken)) {
                    _tokens.push_back(new Token(STRING_CONSTANT, line, column-currentToken.length(), currentToken));
                } else if (isType(currentToken)) {
                    _tokens.push_back(new Token(TYPE, line, column-currentToken.length(), currentToken));
                } else if (isRelop(currentToken)) {
                    _tokens.push_back(new Token(RELOP, line, column-currentToken.length(), currentToken));
                } else if (isOperator(currentToken)) {
                    _tokens.push_back(new Token(OPERATION, line, column-currentToken.length(), currentToken));
                } else if (isIdentifier(currentToken)) {
                    Token* token = new Token(IDENT, line, column-currentToken.length(), currentToken);
                    table->addToken(token);
                    _tokens.push_back(new Token(IDENT, line, column-currentToken.length(), currentToken));
                } else if (isPunctuation(currentToken)) {
                    _tokens.push_back(new Token(PUNCTUATION, line, column-currentToken.length(), currentToken));
                } else {
                    std::string error = "\033[31mUnmatched token:\033[0m " + currentToken;
                    throw std::logic_error(error);
                }
                currentToken.clear();
            }
            currentToken += c;
        } else {
            currentToken += c;
        }

        if (c == '\n') {
            ++line;
            column = 0;
        }
    }

    if (!currentToken.empty()) {
        if (isKeyword(currentToken)) {
            _tokens.push_back(new Token(KEYWORD, line, column-currentToken.length(), currentToken));
        } else if (isIntConstant(currentToken)) {
            _tokens.push_back(new Token(INT_CONSTANT, line, column-currentToken.length(), currentToken));
        } else if (isFloatConstant(currentToken)) {
            _tokens.push_back(new Token(FLOAT_CONSTANT, line, column-currentToken.length(), currentToken));
        } else if (isStringConstant(currentToken)) {
            _tokens.push_back(new Token(STRING_CONSTANT, line, column-currentToken.length(), currentToken));
        } else if (isType(currentToken)) {
            _tokens.push_back(new Token(TYPE, line, column-currentToken.length(), currentToken));
        } else if (isRelop(currentToken)) {
            _tokens.push_back(new Token(RELOP, line, column-currentToken.length(), currentToken));
        } else if (isOperator(currentToken)) {
            _tokens.push_back(new Token(OPERATION, line, column-currentToken.length(), currentToken));
        } else if (isIdentifier(currentToken)) {
            Token* token = new Token(IDENT, line, column-currentToken.length(), currentToken);
            table->addToken(token);
            _tokens.push_back(new Token(IDENT, line, column-currentToken.length(), currentToken));
        } else if (isPunctuation(currentToken)) {
            _tokens.push_back(new Token(PUNCTUATION, line, column-currentToken.length(), currentToken));
        } else {
            std::string error = "\033[31mUnmatched token:\033[0m " + currentToken;
            throw std::logic_error(error);
        }

        parsedAllFile = true;

        return _tokens;
    }
}


Token* Scanner::getNextToken()
{
    if (currentTokenIterator < _tokens.size())
    {
        Token* token = _tokens.at(currentTokenIterator);
        currentTokenIterator++;
        return token;
    }

    if (!parsedAllFile)
    {
        return new Token(WAITING, 0, 0, "WAITING");
    }

    return new Token(END_OF_FILE, 0, 0, "EOF");
}