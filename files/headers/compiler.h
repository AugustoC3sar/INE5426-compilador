#ifndef COMPILER_H
#define COMPILER_H

#include "scanner.h"
#include "parser.h"
#include "symbolTable.h"
#include "token.h"

#include <string>
#include <vector>
#include <iostream>

class Compiler
{
    public:
        /**
         * Constuctor;
         */
        Compiler();

        /**
         * Destructor;
         */
        ~Compiler();

        /**
         * Main method. Compiles the file;
         * 
         * @param file: The whole file converted to a string
         */
        int compile(std::string file);
    
    private:
        Scanner* _scanner;
        Parser* _parser;
        SymbolTable* _table;
        std::string _buffer;
        
};

#endif