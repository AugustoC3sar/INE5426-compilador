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
    if (_type.empty()) {
      _type = tokenType;
    } else {
      throw _token + " is already defined in this scope";
    }
}

void SymbolEntry::removeType() {
    _type = "";
}

std::string SymbolEntry::getType() {
    return _type;
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

std::string SymbolTable::getType(std::string lexicalValue) {
    if (_entries.find(lexicalValue) != _entries.end()) {
        return _entries[lexicalValue].getType();
    }
    throw "reference to " + lexicalValue + " is undefined";
}

// Generates a copy of a symbol table to use in another scope.
SymbolTable* SymbolTable::copy() {
    SymbolTable *symbolTableCopy = new SymbolTable();

    for (const auto& pair : _entries) {
        const std::string& token = pair.first;
        const SymbolEntry& entry = pair.second;

        SymbolEntry entryCopy(entry);
        symbolTableCopy->_entries[token] = entryCopy;
        symbolTableCopy->_entries[token].removeType();
    }

    return symbolTableCopy;
}
