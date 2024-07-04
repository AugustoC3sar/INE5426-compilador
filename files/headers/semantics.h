#ifndef SEMANTICS_ANALYZER_H
#define SEMANTICS_ANALYZER_H

#include <symbolTable.h>
#include <parser.h>

#include <string>

class AddTypeSemanticAction : public SemanticAction {
public:
  std::string name;
  NonTerminal *parent;
  SymbolTable *symbolTable;
  
  AddTypeSemanticAction(NonTerminal *p, SymbolTable *st) {
    name = "ADD_TYPE";
    parent = p;
    symbolTable = st;
  }

  std::string value() override {
    return name;
  }

  void execute() override {
    Item type = parent->children.at(0);
    Item ident = parent->children.at(1);
    symbolTable->addTokenType(ident.terminal->lexicalValue, type.nonTerminal->type);
  }
};

class InheritedTypeSemanticAction : public SemanticAction {
public:
  std::string name;
  NonTerminal *parent;
  
  InheritedTypeSemanticAction(NonTerminal *p) {
    name = "INHERITED_TYPE";
    parent = p;
  }

  std::string value() override {
    return name;
  }

  void execute() override {
    Item arrayvardecl = parent->children.at(3);
    Item type = parent->children.at(0);
    arrayvardecl.nonTerminal->inhType = type.type; 
  }
};

class SynthesizedTypeSemanticAction : public SemanticAction {
public:
  std::string name;
  NonTerminal *parent;
  
  SynthesizedTypeSemanticAction(NonTerminal *p) {
    name = "SYNTHESIZED_TYPE";
    parent = p;
  }

  std::string value() override {
    return name;
  }

  void execute() override {
    NonTerminal* vardecl = parent;
    Item arrayvardecl = parent->children.at(3);
    vardecl->type = arrayvardecl.nonTerminal->type; 
  }
};

class ArrayInheritedTypeSemanticAction : public SemanticAction {
public:
  std::string name;
  NonTerminal *parent;
  
  ArrayInheritedTypeSemanticAction(NonTerminal *p) {
    name = "ARRAY_INHERITED_TYPE";
    parent = p;
  }

  std::string value() override {
    return name;
  }

  void execute() override {
    NonTerminal* arrayvardecl = parent;
    Item arrayvardecl1 = parent->children.at(4);
    Item intConstant = parent->children.at(1);
    arrayvardecl1.nonTerminal->inhType = "array(" + arrayvardecl->inhType + ", " + intConstant.terminal->lexicalValue + ")"; 
  }
};

class ArraySynthesizedTypeSemanticAction : public SemanticAction {
public:
  std::string name;
  NonTerminal *parent;
  
  ArraySynthesizedTypeSemanticAction(NonTerminal *p) {
    name = "ARRAY_SYNTHESIZED_TYPE";
    parent = p;
  }

  std::string value() override {
    return name;
  }

  void execute() override {
    NonTerminal* arrayvardecl = parent;
    Item arrayvardecl1 = parent->children.at(4);
    arrayvardecl->type = arrayvardecl1.nonTerminal->type;
  }
};

class ArraySynthesizeTypeSemanticAction : public SemanticAction {
public:
  std::string name;
  NonTerminal *parent;
  
  ArraySynthesizeTypeSemanticAction(NonTerminal *p) {
    name = "ARRAY_SYNTHESIZE_TYPE";
    parent = p;
  }

  std::string value() override {
    return name;
  }

  void execute() override {
    NonTerminal* arrayvardecl = parent;
    arrayvardecl->type = arrayvardecl->inhType;
  }
};

class SaveTypeSemanticAction : public SemanticAction {
public:
  std::string name;
  std::string type;
  NonTerminal *parent;
  
  SaveTypeSemanticAction(std::string t, NonTerminal *p) {
    name = "SAVE_TYPE";
    parent = p;
    type = t;
  }

  std::string value() override {
    return name;
  }

  void execute() override {
    parent->type = type;
  }
};

class InheritedType : public Item {
public:
  InheritedType(NonTerminal *p) {
    semanticAction = new InheritedTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class SynthesizedType : public Item {
public:
  SynthesizedType(NonTerminal *p) {
    semanticAction = new SynthesizedTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class ArrayInheritedType : public Item {
public:
  ArrayInheritedType(NonTerminal *p) {
    semanticAction = new ArrayInheritedTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class ArraySynthesizedType : public Item {
public:
  ArraySynthesizedType(NonTerminal *p) {
    semanticAction = new ArraySynthesizedTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class ArraySynthesizeType : public Item {
public:
  ArraySynthesizeType(NonTerminal *p) {
    semanticAction = new ArraySynthesizeTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class SaveType : public Item {
public:
  SaveType(std::string t, NonTerminal *p) {
    semanticAction = new SaveTypeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class AddType : public Item {
public:
  AddType(NonTerminal *p, SymbolTable *st) {
    semanticAction = new AddTypeSemanticAction(p, st);
    type = SEMANTIC_ACTION;
  }
};

#endif
