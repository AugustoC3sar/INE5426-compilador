#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "token.h"

#include <unordered_map>
#include <string>
#include <vector>

struct SymbolOccurrence
{
    int column, row;
};

class SymbolEntry
{
private:
    std::string _token;
    std::vector<SymbolOccurrence> _occurrences;
    std::string _type;

public:
    SymbolEntry() = default;
    SymbolEntry(std::string token);

    void addOccurrence(int column, int row);
    void setType(std::string tokenType);
};

class SymbolTable
{
private:
    std::unordered_map<std::string, SymbolEntry> _entries;

public:
    SymbolTable() = default;

    void addToken(Token* token);
    void addTokenType(std::string token, std::string type);
};

#endif