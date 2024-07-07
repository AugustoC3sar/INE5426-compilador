#ifndef CODE_GEN_H
#define CODE_GEN_H

#include <parser.h>

class GenerateAtribstatCodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  GenerateAtribstatCodeSemanticAction(NonTerminal *p)
  {
    name = "GENERATE_ATRIBST_CODE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    Item lvalue = parent->children.at(0);
    Item atribstat_linha = parent->children.at(2);
    parent->code = lvalue.nonTerminal->code + atribstat_linha.nonTerminal->code +  lvalue.nonTerminal->returnT + " = " + atribstat_linha.nonTerminal->returnT + '\n' ;
  }
};

class GenerateAtribstatCode : public Item
{
public:
  GenerateAtribstatCode(NonTerminal *p)
  {
    semanticAction = new GenerateAtribstatCodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class GenerateLvalueCodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;
  TemporaryVariable *_t;

  GenerateLvalueCodeSemanticAction(NonTerminal *p, TemporaryVariable *t)
  {
    name = "GENERATE_LVALUE_CODE";
    parent = p;
    _t = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    Item ident = parent->children.at(0);
    std::string newT = _t->newT();
    parent->returnT = newT;
    parent->code = newT + " = " + ident.terminal->lexicalValue + '\n';
  }
};

class GenerateLvalueCode : public Item
{
public:
  GenerateLvalueCode(NonTerminal *p, TemporaryVariable *t)
  {
    semanticAction = new GenerateLvalueCodeSemanticAction(p, t);
    type = SEMANTIC_ACTION;
  }
};

class SynthesizeLvalueTypeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  SynthesizeLvalueTypeSemanticAction(NonTerminal *p)
  {
    name = "SYNTHESIZE_LVALUE_TYPE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    Item lvalueLinha = parent->children.at(2);
    parent->type = lvalueLinha.nonTerminal->type;
  }
};

class SynthesizeLvalueType : public Item
{
public:
  SynthesizeLvalueType(NonTerminal *p)
  {
    semanticAction = new SynthesizeLvalueTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class InheritLvalueTypeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  InheritLvalueTypeSemanticAction(NonTerminal *p)
  {
    name = "SYNTHESIZE_LVALUE_TYPE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    Item lvalueLinha = parent->children.at(2);
    Item ident = parent->children.at(0);
    lvalueLinha.nonTerminal->inhType = parent->symbolTable->getType(ident.terminal->lexicalValue);
  }
};

class InheritLvalueType : public Item
{
public:
  InheritLvalueType(NonTerminal *p)
  {
    semanticAction = new InheritLvalueTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class InheritLvalueLinhaTypeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  InheritLvalueLinhaTypeSemanticAction(NonTerminal *p)
  {
    name = "INHERIT_LvALUE_LINHA_TYPE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    Item numexpressionRec = parent->children.at(1);
    numexpressionRec.nonTerminal->inhType = parent->inhType;
  }
};

class InheritLvalueLinhaType : public Item
{
public:
  InheritLvalueLinhaType(NonTerminal *p)
  {
    semanticAction = new InheritLvalueLinhaTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class SynthesizeLvalueLinhaTypeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  SynthesizeLvalueLinhaTypeSemanticAction(NonTerminal *p)
  {
    name = "SYNTHESIZE_LVALUE_TYPE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    Item numexpressionRec = parent->children.at(1);
    parent->type = numexpressionRec.nonTerminal->type;
  }
};

class SynthesizeLvalueLinhaType : public Item
{
public:
  SynthesizeLvalueLinhaType(NonTerminal *p)
  {
    semanticAction = new SynthesizeLvalueLinhaTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class SynthesizeNumexpressionRecTypeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  SynthesizeNumexpressionRecTypeSemanticAction(NonTerminal *p)
  {
    name = "SYNTHESIZE_NUMEXPRESSION_REC_TYPE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    parent->type = parent->inhType;
  }
};

class SynthesizeNumexpressionRecType : public Item
{
public:
  SynthesizeNumexpressionRecType(NonTerminal *p)
  {
    semanticAction = new SynthesizeNumexpressionRecTypeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

#endif
