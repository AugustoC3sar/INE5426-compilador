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

std::string SymbolEntry::token() {
    return _token;
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
        return;
    } else {
        SymbolTable *parent = _parent;
        while (parent != nullptr) {
            if (parent->_entries.find(token) != parent->_entries.end()) {
                SymbolEntry entry = SymbolEntry(token);
                _entries[token] = entry;
                _entries[token].setType(type);
                return;
            }
            parent = parent->_parent;
        }
    }
}

std::string SymbolTable::getType(std::string lexicalValue) {
    if (_entries.find(lexicalValue) != _entries.end()) {
        SymbolEntry entry = _entries[lexicalValue];
        std::string type = entry.getType();
        return type;
    }
    
    if (_parent == nullptr) {
        std::string error = "\033[31merror:\033[0m reference to " + lexicalValue + " is undefined";
        throw std::logic_error(error);
    }

    return _parent->getType(lexicalValue);
}

SymbolTable* SymbolTable::newChildSymbolTable() {
    SymbolTable *symbolTable = new SymbolTable();
    _children.push_back(symbolTable);
    symbolTable->_parent = this;
    return symbolTable;
}

void SymbolTable::print() {
    std::cout << "Printing symbol table located at " << this << std::endl;
    for (auto it : _entries) {
        auto entry = it.second;
        std::cout << entry.token() << ": " << entry.getType() << std::endl; 
    }
    std::cout << std::endl;

    if (_children.size() == 0) {
        return;
    }

    for (auto child : _children) {
        child->print();
    }
}
