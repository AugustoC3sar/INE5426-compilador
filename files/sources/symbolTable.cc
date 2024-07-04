#include "symbolTable.h"

SymbolEntry::SymbolEntry(std::string tokenType)
    : _token{tokenType}
{
}

void SymbolEntry::addOccurrence(int column, int row)
{
    struct SymbolOccurrence occurrence;
    occurrence.column = column;
    occurrence.row = row;
    _occurrences.push_back(occurrence);
}

void SymbolEntry::setType(std::string tokenType)
{
    _type = tokenType;
}

void SymbolTable::addToken(Token* token)
{
    bool containsEntry = !(_entries.find(token->value()) == _entries.end());
    if (!containsEntry)
    {
        _entries[token->value()] = SymbolEntry(token->value());
    }
    _entries[token->value()].addOccurrence(token->column(), token->line());
}

void SymbolTable::addTokenType(std::string token, std::string type)
{
    if (_entries.find(token) != _entries.end())
    {
        _entries[token].setType(type);
    }
}