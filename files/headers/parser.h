#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "node.h"
#include "temporaryVariable.h"

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

enum ItemType {
  NON_TERMINAL,
  TERMINAL,
  SEMANTIC_ACTION,
};

class Item;

class NonTerminal {
public:
  std::string name;
  NonTerminal *parent;
  std::vector<Item> children;

  std::string type;
  std::string inhType;
  Node* node;
  Node* leftNode;
  std::string operationValue;
  std::string scope;

  std::string code;
  std::string returnT;

  SymbolTable *symbolTable = nullptr;

  NonTerminal(std::string n, NonTerminal *p) {
    name = n;
    parent = p;

    if (symbolTable == nullptr && p->symbolTable != nullptr) {
      symbolTable = p->symbolTable;
    }

    scope = p->scope;
  }

  NonTerminal(std::string n, NonTerminal *p, SymbolTable *st) {
    name = n;
    parent = p;
    symbolTable = st;
  }

  std::string value() {
    return name;
  };
};

class SemanticAction  {
public:
  virtual std::string value() = 0;
  virtual void execute() = 0;
};

class Terminal {
public:
  std::string lexicalValue;
  std::string name;
  NonTerminal *parent;

  Terminal(std::string lexVal, std::string n, NonTerminal *p) {
    lexicalValue = lexVal;
    name = n;
    parent = p;
  }

  std::string value() {
    if (name == "IDENT" || name == "INT_CONSTANT" || name == "FLOAT_CONSTANT" || name == "STRING_CONSTANT") {
      std::string lowercaseName = ""; 
      for (char ch : name) { 
          lowercaseName += tolower(ch); 
      } 
      return lowercaseName;
    }
    return lexicalValue;
  };
};

class Item {
public:
  ItemType type;
  NonTerminal *nonTerminal;
  SemanticAction *semanticAction;
  Terminal *terminal;

  Item() = default;

  std::string value() {
    if (type == NON_TERMINAL) {
      return nonTerminal->value();
    } else if (type == TERMINAL) {
      return terminal->value();
    } else {
      return semanticAction->value();
    }
  }
};

class Production {
public:
  int id;
  NonTerminal *head;
  std::vector<Item> tail;

  Production(int i, NonTerminal *h, std::vector<Item> t) {
    head = h;
    id = i;
    tail = t;
  }
};

/**
 * Definition of a lexical analyzer based on the Dragon Book's
 */
class Parser
{
    private:
        std::vector<Item> _stack;
        std::unordered_map<std::string, std::unordered_map<std::string, int>> _parseTable;
        SymbolTable* _symbolTable;
        TemporaryVariable* t = new TemporaryVariable();

    public:
        Parser(SymbolTable* table);

        void parse(std::vector<Token*> tokens);

        std::vector<Item> generateNewTokens(int production, NonTerminal *parent);
};

#endif