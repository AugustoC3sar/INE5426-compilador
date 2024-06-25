#include "LexicalAnalyzer.h"
#include "SymbolTable.h"
#include <fstream>
#include <iostream>
#include <cctype>

bool LexicalAnalyzer::isIdentifier(std::string token)
{
    std::regex identifierPattern("^[a-zA-Z][a-zA-Z0-9_]*$");
    return std::regex_match(token, identifierPattern);
}

bool LexicalAnalyzer::isFloatConstant(std::string token)
{
    std::regex identifierPattern("[+-]?([0-9]*[.])?[0-9]+$");
    return std::regex_match(token, identifierPattern);
}

bool LexicalAnalyzer::isIntConstant(std::string token)
{
    std::regex identifierPattern("[+-]?[0-9]+$");
    return std::regex_match(token, identifierPattern);
}

bool LexicalAnalyzer::isStringConstant(std::string token)
{
    return token.at(0) == '"' && token.at(token.length() - 1) == '"';
}

bool LexicalAnalyzer::isPunctuation(std::string token)
{
    for (std::string punctuation : punctuations)
    {
        if (token == punctuation)
        {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::isRelop(std::string token)
{
    for (std::string relop : relops)
    {
        if (token == relop)
        {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::isType(std::string token)
{
    for (std::string type : types)
    {
        if (token == type)
        {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::isReservedWord(std::string token)
{
    for (std::string reservedWord : reservedWords)
    {
        bool tokenIsReservedWord = token.compare(reservedWord) == 0;
        if (tokenIsReservedWord)
        {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::isOperator(std::string token)
{
    for (std::string op : operators)
    {
        bool tokenIsOperator = token.compare(op) == 0;
        if (tokenIsOperator)
        {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::shouldBreakToken(char character)
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

SymbolTable LexicalAnalyzer::parse(std::string filename)
{
    std::ifstream file(filename);
    SymbolTable symbolTable;

    if (!file.is_open())
    {
        std::cerr << "Não foi possível abrir o arquivo " << filename << std::endl;
        return symbolTable;
    }

    std::string currentToken;
    int column = 0;
    int row = 1;
    while (file.read(buffer, BUFFER_COUNT) || file.gcount() > 0)
    {
        size_t bytesRead = file.gcount();
        for (size_t i = 0; i < bytesRead; ++i)
        {
            char c = buffer[i];
            ++column;
            if (shouldBreakToken(c))
            {
                if (isPunctuation(std::string(1, c)))
                {
                    if (currentToken.empty())
                    {
                        currentToken += c;
                    }
                    else
                    {
                        i--;
                    }
                }

                if (!currentToken.empty())
                {
                    if (isReservedWord(currentToken))
                    {
                        tokens.push_back({RESERVED_WORD, currentToken});
                    }
                    else if (isIntConstant(currentToken))
                    {
                        tokens.push_back({INT_CONSTANT, currentToken});
                    }
                    else if (isFloatConstant(currentToken))
                    {
                        tokens.push_back({FLOAT_CONSTANT, currentToken});
                    }
                    else if (isStringConstant(currentToken))
                    {
                        tokens.push_back({STRING_CONSTANT, currentToken});
                    }
                    else if (isType(currentToken))
                    {
                        tokens.push_back({TYPE, currentToken});
                    }
                    else if (isRelop(currentToken))
                    {
                        tokens.push_back({RELOP, currentToken});
                    }
                    else if (isOperator(currentToken))
                    {
                        tokens.push_back({OPERATION, currentToken});
                    }
                    else if (isIdentifier(currentToken))
                    {
                        symbolTable.addTokenOccurence(currentToken, column - currentToken.length(), row);
                        tokens.push_back({IDENT, currentToken});
                    }
                    else if (isPunctuation(currentToken))
                    {
                        tokens.push_back({PUNCTUATION, currentToken});
                    }
                    else
                    {
                        std::cerr << "Token não identificado " << currentToken << std::endl;
                        return symbolTable;
                    }
                    currentToken.clear();
                }
            }
            else if (isOperator(std::string(1, c)) || isRelop(std::string(1, c)))
            {
                if (!currentToken.empty())
                {
                    if (isReservedWord(currentToken))
                    {
                        tokens.push_back({RESERVED_WORD, currentToken});
                    }
                    else if (isIntConstant(currentToken))
                    {
                        tokens.push_back({INT_CONSTANT, currentToken});
                    }
                    else if (isFloatConstant(currentToken))
                    {
                        tokens.push_back({FLOAT_CONSTANT, currentToken});
                    }
                    else if (isStringConstant(currentToken))
                    {
                        tokens.push_back({STRING_CONSTANT, currentToken});
                    }
                    else if (isType(currentToken))
                    {
                        tokens.push_back({TYPE, currentToken});
                    }
                    else if (isRelop(currentToken))
                    {
                        tokens.push_back({RELOP, currentToken});
                    }
                    else if (isOperator(currentToken))
                    {
                        tokens.push_back({OPERATION, currentToken});
                    }
                    else if (isIdentifier(currentToken))
                    {
                        symbolTable.addTokenOccurence(currentToken, column - currentToken.length(), row);
                        tokens.push_back({IDENT, currentToken});
                    }
                    else if (isPunctuation(currentToken))
                    {
                        tokens.push_back({PUNCTUATION, currentToken});
                    }
                    else
                    {
                        std::cerr << "Token não identificado " << currentToken << std::endl;
                        return symbolTable;
                    }
                    currentToken.clear();
                }
                currentToken += c;
            }
            else
            {
                currentToken += c;
            }

            if (c == '\n')
            {
                ++row;
                column = 0;
            }
        }
    }

    if (!currentToken.empty())
    {
        if (isReservedWord(currentToken))
        {
            tokens.push_back({RESERVED_WORD, currentToken});
        }
        else if (isIntConstant(currentToken))
        {
            tokens.push_back({INT_CONSTANT, currentToken});
        }
        else if (isFloatConstant(currentToken))
        {
            tokens.push_back({FLOAT_CONSTANT, currentToken});
        }
        else if (isStringConstant(currentToken))
        {
            tokens.push_back({STRING_CONSTANT, currentToken});
        }
        else if (isType(currentToken))
        {
            tokens.push_back({TYPE, currentToken});
        }
        else if (isRelop(currentToken))
        {
            tokens.push_back({RELOP, currentToken});
        }
        else if (isOperator(currentToken))
        {
            tokens.push_back({OPERATION, currentToken});
        }
        else if (isIdentifier(currentToken))
        {
            symbolTable.addTokenOccurence(currentToken, column - currentToken.length(), row);
            tokens.push_back({IDENT, currentToken});
        }
        else if (isPunctuation(currentToken))
        {
            tokens.push_back({PUNCTUATION, currentToken});
        }
        else
        {
            std::cerr << "Token não identificado " << currentToken << std::endl;
            return symbolTable;
        }
    }

    parsedAllFile = true;

    file.close();
    return symbolTable;
}

Token LexicalAnalyzer::getNextToken()
{
    if (currentTokenIterator < tokens.size())
    {
        Token token = tokens.at(currentTokenIterator);
        currentTokenIterator++;
        return token;
    }

    if (!parsedAllFile)
    {
        return {WAITING, "WAITING"};
    }

    return {END_OF_FILE, "EOF"};
}