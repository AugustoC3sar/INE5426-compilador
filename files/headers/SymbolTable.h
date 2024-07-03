#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <vector>
#include "token.h"

class SymbolTable {

    private:
        std::vector<Token*> entries;

    public:
        SymbolTable() {};

        void addToken(Token* token){ entries.push_back(token); };
};

#endif