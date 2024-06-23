#include "SymbolTable.h"

SymbolEntry::SymbolEntry(std::string tokenType)
    : token{tokenType}
{
}

void SymbolEntry::addOccurrence(int column, int row)
{
    struct SymbolOccurrence occurrence;
    occurrence.column = column;
    occurrence.row = row;
    occurrences.push_back(occurrence);
}

void SymbolEntry::setType(std::string tokenType)
{
    type = tokenType;
}

void SymbolTable::addTokenOccurence(std::string token, int column, int row)
{
    bool containsEntry = !(entries.find(token) == entries.end());
    if (!containsEntry)
    {
        entries[token] = SymbolEntry(token);
    }
    entries[token].addOccurrence(column, row);
}

void SymbolTable::addTokenType(std::string token, std::string type)
{
    if (entries.find(token) != entries.end())
    {
        entries[token].setType(type);
    }
}
