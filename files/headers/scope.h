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
    Item firstChild = parent->children.at(parent->children.size()-1);
    SymbolTable* symbolTableCopy = symbolTable->copy();
    firstChild.nonTerminal->symbolTable = symbolTableCopy;
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
