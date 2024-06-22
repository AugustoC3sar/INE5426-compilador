#include <LexicalAnalyzer.h>
#include <SymbolTable.h>

int main() {
    LexicalAnalyzer *lexicalAnalyzer = new LexicalAnalyzer();

    SymbolTable symbolTable = lexicalAnalyzer->parse("test");

    return 0;
}
