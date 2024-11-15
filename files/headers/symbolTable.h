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
        /**
         * Constructor
         */
        SymbolEntry() = default;
        SymbolEntry(std::string token) : _token{token} {};

        /**
         * Add ocurrence to symbol entry
         * 
         * @param row: file row of the occurrence
         * @param column: file column of the occurrence
         */
        void addOccurrence(unsigned int row, unsigned int column);

        /**
         * Getter
         * 
         * @return semantic type of the token
         */
        std::string getType();

        /**
         * Getter
         * 
         * @return the token in this entry.
        */
       std::string token();

        /**
         * Sets the semantic type of the token
         * 
         * @param tokenType: semantic type of the token
         */
        void setType(std::string tokenType);
};

class SymbolTable
{
private:
    SymbolTable* _parent;
    std::vector<SymbolTable*> _children = {};
    std::unordered_map<std::string, SymbolEntry> _entries;

public:
    /**
     * Constructor
    */
    SymbolTable() = default;

    /**
     * Adds a token to the table
     * 
     * @param token: token value
     * @param row: file row of the occurrence
     * @param column: file column of the occurrence
     */
    void addToken(std::string token, unsigned int row, unsigned int column);
    
    /**
     * Define a token's semantic type
     * 
     * @param token: token value
     * @param type: semantic type of the token
     */
    void addTokenType(std::string token, std::string type);

    /**
     * Getter
     * 
     * @return semantic type of a given lexical value
     */
    std::string getType(std::string lexicalValue);

    /**
     * Generates a new children SymbolTable.
     * 
     * @return SymbolTable: a new children SymbolTable.
    */
    SymbolTable* newChildSymbolTable();

    /**
     * Print all symbol tables.
    */
   void print();
};

#endif