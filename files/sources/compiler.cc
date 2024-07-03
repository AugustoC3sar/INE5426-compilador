#include "../headers/compiler.h"

Compiler::Compiler()
{
    _scanner = new Scanner();
    _parser = new Parser();
    _table = new SymbolTable();
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
        std::cerr << e.what() << '\n';
        return -1;
    }

    for (auto token : tokens){
        std::cout << "Token " << token->value() << std::endl;
        std::cout << "line = " << token->line() << std::endl;
        std::cout << "column = " << token->line() << std::endl;
        std::cout << "====================" << std::endl;
    }

    // Parsing the file (tokens)
    try
    {
        _parser->parse(tokens);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}