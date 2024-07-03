#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

#include <iostream>

int main()
{
    LexicalAnalyzer *lexicalAnalyzer = new LexicalAnalyzer();
    SyntaxAnalyzer *syntaxAnalyzer = new SyntaxAnalyzer(lexicalAnalyzer);
    lexicalAnalyzer->parse("test");
    syntaxAnalyzer->parse();

    return 0;
}
