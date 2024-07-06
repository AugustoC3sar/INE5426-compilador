#include "compiler.h"

Compiler::Compiler()
{
    _scanner = new Scanner();
    _table = new SymbolTable();
    _parser = new Parser(_table);
}

Compiler::~Compiler()
{
    delete _scanner;
    delete _parser;
    delete _table;
}

int Compiler::compile(std::string file)
{
    std::vector<Token*> tokens;

    // Scan file looking for tokens
    try
    {
        tokens = _scanner->scan(file, _table);
    }
    catch(const std::exception& e)
    {
        std::cerr << "\033[1mconvcc: " << e.what() << '\n';
        return -1;
    }

    // Printing tokens
    for (auto token : tokens){
        std::cout << token->value() << std::endl;
    }

    /* // Parsing the file (tokens)
    try
    {
        _parser->parse(tokens);
    }
    catch(const std::exception& e)
    {
        std::cerr << "\033[1mconvcc: " << e.what() << '\n';
        return -1;
    } */

    return 0;
}