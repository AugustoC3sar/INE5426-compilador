#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include "LexicalAnalyzer.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>
#include <variant>

class Item {
public:
  virtual std::string value();
  virtual void execute();
};

class SemanticAction : public Item {
public:
  std::string name;

  std::string value() {
    return name;
  };

  void execute() {}
};

class NonTerminal : public Item {
public:
  std::string name;
  NonTerminal *parent;

  NonTerminal(std::string n, NonTerminal *p) {
    name = n;
    parent = p;
  }

  std::string value() {
    return name;
  };

  void execute() {}
};

class Terminal : public Item {
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
    return name;
  };

  void execute() {}
};

class Epsilon : public Terminal {
public:
  Epsilon(NonTerminal *p) : Terminal("&", "EPSILON", p) {}
};

class Def : public Terminal {
public:
  Def(NonTerminal *p) : Terminal("def", "DEF", p) {}
};

class Ident : public Terminal {
public:
  Ident(std::string lexicalValue, NonTerminal *p) : Terminal(lexicalValue, "IDENT", p) {}
};

class OpenParentheses : public Terminal {
public:
  OpenParentheses(NonTerminal *p) : Terminal("(", "OPEN_PARENTHESES", p) {}
};

class CloseParentheses : public Terminal {
public:
  CloseParentheses(NonTerminal *p) : Terminal(")", "CLOSE_PARENTHESES", p) {}
};

class OpenBrackets : public Terminal {
public:
  OpenBrackets(NonTerminal *p) : Terminal("{", "OPEN_BRACKETS", p) {}
};

class CloseBrackets : public Terminal {
public:
  CloseBrackets(NonTerminal *p) : Terminal("}", "CLOSE_BRACKETS", p) {}
};

class Int : public Terminal {
public:
  Int(NonTerminal *p) : Terminal("int", "INT", p) {}
};

class Float : public Terminal {
public:
  Float(NonTerminal *p) : Terminal("float", "FLOAT", p) {}
};

class String : public Terminal {
public:
  String(NonTerminal *p) : Terminal("string", "STRING", p) {}
};

class Comma : public Terminal {
public:
  Comma(NonTerminal *p) : Terminal(",", "COMMA", p) {}
};

class Semicolon : public Terminal {
public:
  Semicolon(NonTerminal *p) : Terminal(";", "SEMICOLON", p) {}
};

class Break : public Terminal {
public:
  Break(NonTerminal *p) : Terminal("break", "BREAK", p) {}
};

class OpenSquareBrackets : public Terminal {
public:
  OpenSquareBrackets(NonTerminal *p) : Terminal("[", "OPEN_SQUARE_BRACKETS", p) {}
};

class CloseSquareBrackets : public Terminal {
public:
  CloseSquareBrackets(NonTerminal *p) : Terminal("]", "CLOSE_SQUARE_BRACKETS", p) {}
};

class Equal : public Terminal {
public:
  Equal(NonTerminal *p) : Terminal("=", "EQUAL", p) {}
};

class Call : public Terminal {
public:
  Call(NonTerminal *p) : Terminal("call", "CALL", p) {}
};

class Print : public Terminal {
public:
  Print(NonTerminal *p) : Terminal("print", "PRINT", p) {}
};

class Read : public Terminal {
public:
  Read(NonTerminal *p) : Terminal("read", "READ", p) {}
};

class Return : public Terminal {
public:
  Return (NonTerminal *p) : Terminal("return", "RETURN", p) {}
};

class If : public Terminal {
public:
  If(NonTerminal *p) : Terminal("if", "IF", p) {}
};

class Else : public Terminal {
public:
  Else(NonTerminal *p) : Terminal("else", "ELSE", p) {}
};

class For : public Terminal {
public:
  For(NonTerminal *p) : Terminal("for", "FOR", p) {}
};

class New : public Terminal {
public:
  New(NonTerminal *p) : Terminal("new", "NEW", p) {}
};

class GreaterThan : public Terminal {
public:
  GreaterThan(NonTerminal *p) : Terminal(">", "GREATER_THAN", p) {}
};

class LessThan : public Terminal {
public:
  LessThan(NonTerminal *p) : Terminal("<", "LESS_THAN", p) {}
};

class LessOrEquals : public Terminal {
public:
  LessOrEquals(NonTerminal *p) : Terminal("<=", "LESS_OR_EQUALS", p) {}
};

class GreaterOrEquals : public Terminal {
public:
  GreaterOrEquals(NonTerminal *p) : Terminal(">=", "GREATER_OR_EQUALS", p) {}
};

class Equals : public Terminal {
public:
  Equals(NonTerminal *p) : Terminal("==", "EQUALS", p) {}
};

class Different : public Terminal {
public:
  Different(NonTerminal *p) : Terminal("!=", "DIFFERENT", p) {}
};

class Minus : public Terminal {
public:
  Minus(NonTerminal *p) : Terminal("-", "MINUS", p) {}
};

class Positive : public Terminal {
public:
  Positive(NonTerminal *p) : Terminal("+", "POSITIVE", p) {}
};

class Times : public Terminal {
public:
  Times(NonTerminal *p) : Terminal("*", "TIMES", p) {}
};

class Divide : public Terminal {
public:
  Divide(NonTerminal *p) : Terminal("/", "DIVIDE", p) {}
};

class Remainder : public Terminal {
public:
  Remainder(NonTerminal *p) : Terminal("%", "REMAINDER", p) {}
};

class IntConstant : public Terminal {
public:
  IntConstant(std::string lexicalValue, NonTerminal *p) : Terminal(lexicalValue, "INT_CONSTANT", p) {}
};

class FloatConstant : public Terminal {
public:
  FloatConstant(std::string lexicalValue, NonTerminal *p) : Terminal(lexicalValue, "FLOAT_CONSTANT", p) {}
};

class StringConstant : public Terminal {
public:
  StringConstant(std::string lexicalValue, NonTerminal *p) : Terminal(lexicalValue, "STRING_CONSTANT", p) {}
};

class Null : public Terminal {
public:
  Null(NonTerminal *p) : Terminal("null", "NULL", p) {}
};

class Program : public NonTerminal {
public:
  Program(NonTerminal *parent) : NonTerminal("PROGRAM", parent) {}
};

class Statement : public NonTerminal {
public:
  Statement(NonTerminal *parent) : NonTerminal("STATEMENT", parent) {}
};

class Funclist : public NonTerminal {
public:
  Funclist(NonTerminal *parent) : NonTerminal("FUNCLIST", parent) {}
};

class Funcdef : public NonTerminal {
public:
  Funcdef(NonTerminal *parent) : NonTerminal("FUNCDEF", parent) {}
};

class Type : public NonTerminal {
public:
  Type(NonTerminal *parent) : NonTerminal("TYPE", parent) {}
};

class Paramlist : public NonTerminal {
public:
  Paramlist(NonTerminal *parent) : NonTerminal("PARAMLIST", parent) {}
};

class Vardecl : public NonTerminal {
public:
  Vardecl(NonTerminal *parent) : NonTerminal("VARDECL", parent) {}
};

class Arrayvardecl : public NonTerminal {
public:
  Arrayvardecl(NonTerminal *parent) : NonTerminal("ARRAYVARDECL", parent) {}
};

class Atribstat : public NonTerminal {
public:
  Atribstat(NonTerminal *parent) : NonTerminal("ATRIBSTAT", parent) {}
};

class Funccall : public NonTerminal {
public:
  Funccall(NonTerminal *parent) : NonTerminal("FUNCCALL", parent) {}
};

class Paramlistcall : public NonTerminal {
public:
  Paramlistcall(NonTerminal *parent) : NonTerminal("PARAMLISTCALL", parent) {}
};


class Paramlistcalla : public NonTerminal {
public:
  Paramlistcalla(NonTerminal *parent) : NonTerminal("PARAMLISTCALL'", parent) {}
};

class Printstat : public NonTerminal {
public:
  Printstat(NonTerminal *parent) : NonTerminal("PRINTSTAT", parent) {}
};

class ReadStat : public NonTerminal {
public:
  ReadStat(NonTerminal *parent) : NonTerminal("READSTAT", parent) {}
};

class ReturnStat : public NonTerminal {
public:
  ReturnStat(NonTerminal *parent) : NonTerminal("RETURNSTAT", parent) {}
};

class Ifstat : public NonTerminal {
public:
  Ifstat(NonTerminal *parent) : NonTerminal("IFSTAT", parent) {}
};

class Elsestat : public NonTerminal {
public:
  Elsestat(NonTerminal *parent) : NonTerminal("ELSESTAT", parent) {}
};

class Forstat : public NonTerminal {
public:
  Forstat(NonTerminal *parent) : NonTerminal("FORSTAT", parent) {}
};

class Statelist : public NonTerminal {
public:
  Statelist(NonTerminal *parent) : NonTerminal("STATELIST", parent) {}
};

class Statelista : public NonTerminal {
public:
  Statelista(NonTerminal *parent) : NonTerminal("STATELIST'", parent) {}
};

class Allocexpression : public NonTerminal {
public:
  Allocexpression(NonTerminal *parent) : NonTerminal("ALLOCEXPRESION", parent) {}
};

class Numlist : public NonTerminal {
public:
  Numlist(NonTerminal *parent) : NonTerminal("NUM_LIST", parent) {}
};

class Numlista : public NonTerminal {
public:
  Numlista(NonTerminal *parent) : NonTerminal("NUM_LIST'", parent) {}
};

class Relop : public NonTerminal {
public:
  Relop(NonTerminal *parent) : NonTerminal("RELOP", parent) {}
};

class Expression : public NonTerminal {
public:
  Expression(NonTerminal *parent) : NonTerminal("EXPRESSION", parent) {}
};

class Expressiona : public NonTerminal {
public:
  Expressiona(NonTerminal *parent) : NonTerminal("EXPRESSION'", parent) {}
};

class Signal : public NonTerminal {
public:
  Signal(NonTerminal *parent) : NonTerminal("SIGNAL", parent) {}
};

class Numexpression : public NonTerminal {
public:
  Numexpression(NonTerminal *parent) : NonTerminal("NUMEXPRESSION", parent) {}
};

class Numexpressiona : public NonTerminal {
public:
  Numexpressiona(NonTerminal *parent) : NonTerminal("NUMEXPRESSION'", parent) {}
};

class Termrec : public NonTerminal {
public:
  Termrec(NonTerminal *parent) : NonTerminal("TERM_REC", parent) {}
};

class Termreca : public NonTerminal {
public:
  Termreca(NonTerminal *parent) : NonTerminal("TERM_REC'", parent) {}
};

class Operator : public NonTerminal {
public:
  Operator(NonTerminal *parent) : NonTerminal("OPERATOR", parent) {}
};

class Term : public NonTerminal {
public:
  Term(NonTerminal *parent) : NonTerminal("TERM", parent) {}
};

class Terma : public NonTerminal {
public:
  Terma(NonTerminal *parent) : NonTerminal("TERM'", parent) {}
};


class Unaryexprrec : public NonTerminal {
public:
  Unaryexprrec(NonTerminal *parent) : NonTerminal("UNARYEXPR_REC", parent) {}
};

class Unaryexprreca : public NonTerminal {
public:
  Unaryexprreca(NonTerminal *parent) : NonTerminal("UNARYEXPR_REC'", parent) {}
};

class Unaryexpr : public NonTerminal {
public:
  Unaryexpr(NonTerminal *parent) : NonTerminal("UNARYEXPR", parent) {}
};

class Factor : public NonTerminal {
public:
  Factor(NonTerminal *parent) : NonTerminal("FACTOR", parent) {}
};

class Lvalue : public NonTerminal {
public:
  Lvalue(NonTerminal *parent) : NonTerminal("LVALUE", parent) {}
};

class Numexpressionrec : public NonTerminal {
public:
  Numexpressionrec(NonTerminal *parent) : NonTerminal("NUMEXPRESSION_REC", parent) {}
};

class Numexpressionreca : public NonTerminal {
public:
  Numexpressionreca(NonTerminal *parent) : NonTerminal("NUMEXPRESSION_REC'", parent) {}
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

class SyntaxAnalyzer
{
private:
  std::vector<Item> stack;
  std::unordered_map<std::string, std::unordered_map<std::string, int>> parseTable;
  LexicalAnalyzer *lexicalAnalyzer;

public:
  SyntaxAnalyzer(LexicalAnalyzer *la);

  void parse();

  std::vector<Item> generateNewTokens(int production, NonTerminal *parent);
};

#endif