#include "symbolTable.h"
#include <iostream>


void SymbolEntry::addOccurrence(unsigned int row, unsigned int column)
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


void SymbolTable::addToken(std::string token, unsigned int row, unsigned int column)
{
    bool containsEntry = !(_entries.find(token) == _entries.end());
    if (!containsEntry)
    {
        _entries[token] = SymbolEntry(token);
    }
    _entries[token].addOccurrence(row, column);
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

    std::string error = "\033[31merror:\033[0m reference to " + lexicalValue + " is undefined";
    throw std::logic_error(error);
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
