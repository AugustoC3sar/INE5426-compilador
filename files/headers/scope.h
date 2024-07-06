#ifndef SCOPE_H
#define SCOPE_H

#include <parser.h>


class NewScopeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;
  SymbolTable* symbolTable;

  NewScopeSemanticAction(NonTerminal *p, SymbolTable *st)
  {
    name = "NEW_SCOPE";
    parent = p;
    symbolTable = st;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    Item firstChild = parent->children.at(1);
    if (parent->symbolTable != nullptr) {
        firstChild.nonTerminal->symbolTable = symbolTable;
    } else {
        firstChild.nonTerminal->symbolTable = parent->symbolTable;
    }
  }
};

class NewScope : public Item
{
public:
  NewScope(NonTerminal *p, SymbolTable *st)
  {
    semanticAction = new NewScopeSemanticAction(p, st);
    type = SEMANTIC_ACTION;
  }
};

#endif
