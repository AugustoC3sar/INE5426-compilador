#include <LexicalAnalyzer.h>
#include <SymbolTable.h>

#include <iostream>

int main()
{
    LexicalAnalyzer *lexicalAnalyzer = new LexicalAnalyzer();

    SymbolTable symbolTable = lexicalAnalyzer->parse("test");

    Token token = lexicalAnalyzer->getNextToken();
    while (token.type != END_OF_FILE)
    {
        std::cout << "Token type: " << token.type << " Token value: " << token.value << std::endl;
        token = lexicalAnalyzer->getNextToken();
    }

    return 0;
}
