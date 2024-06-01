#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>
#include <vector>

struct SymbolOccurrence {
    int column, row;
};

class SymbolEntry {
private:
    std::string token;
    std::vector<SymbolOccurrence> occurrences;
    std::string type;

public:
    SymbolEntry() = default;
    SymbolEntry(std::string token);

    void addOccurrence(int column, int row);
    void setType(std::string tokenType);
};

class SymbolTable {
private:
    std::unordered_map<std::string, SymbolEntry> entries;

public:
    SymbolTable() = default;

    void addTokenOccurence(std::string token, int column, int row);
    void addTokenType(std::string token, std::string type);
};

#endif