#ifndef NODE_H
#define NODE_H

#include <symbolTable.h>
#include <temporaryVariable.h>

#include <string>

class Node
{
private:
    Node *_left = nullptr;
    Node *_right = nullptr;
    std::string _lexicalValue;
    std::string _t;

public:
    Node(std::string lexVal, Node *l, Node *r);
    Node(std::string lexVal);

    std::string getExpressionType(SymbolTable *symbolTable);
    std::string code(TemporaryVariable *t);
    void printLeftFromRight();
};

#endif
