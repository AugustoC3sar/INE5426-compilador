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
        std::string error = "\033[31merror:\033[0m " + _token + " is already defined in this scope";
        throw std::logic_error(error);
    }
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
    if (_entries.find(token) != _entries.end()) {
        _entries[token].setType(type);
    } else if (_parent->_entries.find(token) != _parent->_entries.end()) {
        SymbolEntry entry = SymbolEntry(token);
        _entries[token] = entry;
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

SymbolTable* SymbolTable::newChildSymbolTable() {
    SymbolTable *symbolTable = new SymbolTable();
    _children.push_back(symbolTable);
    symbolTable->_parent = this;
    return symbolTable;
}
