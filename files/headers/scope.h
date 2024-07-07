#ifndef SCOPE_H
#define SCOPE_H

#include <parser.h>

class NewScopeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  NewScopeSemanticAction(NonTerminal *p)
  {
    name = "NEW_SCOPE";
    parent = p;
    parent->scope = p->value();
    for (auto child : parent->children) {
      if (child.nonTerminal != nullptr) {
        child.nonTerminal->scope = parent->scope;
      }
    }
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    Item firstChild = parent->children.at(1);
    SymbolTable* symbolTableCopy = parent->symbolTable->newChildSymbolTable();
    firstChild.nonTerminal->symbolTable = symbolTableCopy;
  }
};

class NewScope : public Item
{
public:
  NewScope(NonTerminal *p)
  {
    semanticAction = new NewScopeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class CheckBreakInScopeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  CheckBreakInScopeSemanticAction(NonTerminal *p)
  {
    name = "CHECK_BREAK_IN_SCOPE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    if (parent->scope != "FORSTAT") {
      std::string error = "break outside for loop";
      throw std::logic_error(error);
    }
  }
};

class CheckBreakInScope : public Item
{
public:
  CheckBreakInScope(NonTerminal *p)
  {
    semanticAction = new CheckBreakInScopeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};


#endif
