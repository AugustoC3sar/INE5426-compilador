#include "LexicalAnalyzer.h"
#include "SymbolTable.h"
#include <fstream>
#include <iostream>
#include <cctype>

bool LexicalAnalyzer::isIdentifier(std::string token) {
    std::regex identifier_pattern("^[a-zA-Z][a-zA-Z0-9_]*[a-zA-Z0-9_]+$");
    return std::regex_match(token, identifier_pattern);
}

bool LexicalAnalyzer::isNumber(std::string token) {
    long unsigned int numberOfDecimals = 0;

    for (long unsigned int i = 0; i < token.length(); i++) {
        char c = token.at(i);
        for (char n : numbers) {
            if (c == n) {
                numberOfDecimals++;
            }
        }
    }

    bool allCharactersAreDecimals = token.length() == numberOfDecimals;
    return allCharactersAreDecimals;
}

bool LexicalAnalyzer::isReservedWord(std::string token) {
    for (std::string reservedWord : reservedWords) {
        bool tokenIsReservedWord = token.compare(reservedWord) == 0;
        if (tokenIsReservedWord) {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::isOperator(std::string token) {
    for (std::string op : operators) {
        bool tokenIsOperator = token.compare(op) == 0;
        if (tokenIsOperator) {
            return true;
        }
    }
    return false;
}

SymbolTable LexicalAnalyzer::parse(std::string filename)
{
    std::ifstream file(filename);
    SymbolTable symbolTable;

    if (!file.is_open())
    {
        std::cerr << "Não foi possível abrir o arquivo" << filename << std::endl;
        return symbolTable;
    }

    std::string currentToken;
    while (file.read(buffer, 16) || file.gcount() > 0)
    {
        size_t bytesRead = file.gcount();
        for (size_t i = 0; i < bytesRead; ++i)
        {
            char c = buffer[i];
            if (isspace(c))
            {
                if (!currentToken.empty())
                {
                    if (isReservedWord(currentToken) || isNumber(currentToken) || isOperator(currentToken))
                    {
                        continue;
                    }
                    else if (isIdentifier(currentToken))
                    {
                        symbolTable.addTokenOccurence(currentToken, 0, 0);
                    }
                    else
                    {
                        std::cerr << "Token não identificado " << currentToken << std::endl;
                        return symbolTable;
                    }
                    currentToken.clear();
                }
            }
            else if (isOperator(std::string(1, c)))
            {
                if (!currentToken.empty())
                {
                    if (isReservedWord(currentToken) || isNumber(currentToken))
                    {
                        continue;
                    }
                    else if (isIdentifier(currentToken))
                    {
                        symbolTable.addTokenOccurence(currentToken, 0, 0);
                    }
                    else
                    {
                        std::cerr << "Token não identificado " << currentToken << std::endl;
                        return symbolTable;
                    }
                    currentToken.clear();
                }
                currentToken += c;
                if (isOperator(currentToken))
                {
                    currentToken.clear();
                }
            }
            else
            {
                currentToken += c;
            }
        }
    }

    if (!currentToken.empty())
    {
        if (isIdentifier(currentToken))
        {
            symbolTable.addTokenOccurence(currentToken, 0, 0);
        }
        else
        {
            std::cerr << "Token não identificado " << currentToken << std::endl;
            return symbolTable;
        }
    }

    file.close();
    return symbolTable;
}