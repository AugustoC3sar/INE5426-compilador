#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include "LexicalAnalyzer.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

class SemanticAction {
public:
  void apply();
};

class NonTerminal {
public:
  std::string name;
  NonTerminal *parent;

  NonTerminal(std::string n, NonTerminal *p) {
    name = n;
    parent = p;
  }
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
};

class Epsilon : Terminal {
public:
  Epsilon(NonTerminal *p) : Terminal("&", "EPSILON", p) {}
};

class Def : Terminal {
public:
  Def(NonTerminal *p) : Terminal("def", "DEF", p) {}
};

class Ident : Terminal {
public:
  Ident(std::string lexicalValue, NonTerminal *p) : Terminal(lexicalValue, "IDENT", p) {}
};

class OpenParentheses : Terminal {
public:
  OpenParentheses(NonTerminal *p) : Terminal("(", "OPEN_PARENTHESES", p) {}
};

class CloseParentheses : Terminal {
public:
  CloseParentheses(NonTerminal *p) : Terminal(")", "CLOSE_PARENTHESES", p) {}
};

class OpenBrackets : Terminal {
public:
  OpenBrackets(NonTerminal *p) : Terminal("{", "OPEN_BRACKETS", p) {}
};

class CloseBrackets : Terminal {
public:
  CloseBrackets(NonTerminal *p) : Terminal("}", "CLOSE_BRACKETS", p) {}
};

class Int : Terminal {
public:
  Int(NonTerminal *p) : Terminal("int", "INT", p) {}
};

class Float : Terminal {
public:
  Float(NonTerminal *p) : Terminal("float", "FLOAT", p) {}
};

class String : Terminal {
public:
  String(NonTerminal *p) : Terminal("string", "STRING", p) {}
};

class Comma : Terminal {
public:
  Comma(NonTerminal *p) : Terminal(",", "COMMA", p) {}
};

class Semicolon : Terminal {
public:
  Semicolon(NonTerminal *p) : Terminal(";", "SEMICOLON", p) {}
};

class Break : Terminal {
public:
  Break(NonTerminal *p) : Terminal("break", "BREAK", p) {}
};

class OpenSquareBrackets : Terminal {
public:
  OpenSquareBrackets(NonTerminal *p) : Terminal("[", "OPEN_SQUARE_BRACKETS", p) {}
};

class CloseSquareBrackets : Terminal {
public:
  CloseSquareBrackets(NonTerminal *p) : Terminal("]", "CLOSE_SQUARE_BRACKETS", p) {}
};

class Equal : Terminal {
public:
  Equal(NonTerminal *p) : Terminal("=", "EQUAL", p) {}
};

class Call : Terminal {
public:
  Call(NonTerminal *p) : Terminal("call", "CALL", p) {}
};

class Print : Terminal {
public:
  Print(NonTerminal *p) : Terminal("print", "PRINT", p) {}
};

class Read : Terminal {
public:
  Read(NonTerminal *p) : Terminal("read", "READ", p) {}
};

class Return : Terminal {
public:
  Return (NonTerminal *p) : Terminal("return", "RETURN", p) {}
};

class If : Terminal {
public:
  If(NonTerminal *p) : Terminal("if", "IF", p) {}
};

class Else : Terminal {
public:
  Else(NonTerminal *p) : Terminal("else", "ELSE", p) {}
};

class For : Terminal {
public:
  For(NonTerminal *p) : Terminal("for", "FOR", p) {}
};

class New : Terminal {
public:
  New(NonTerminal *p) : Terminal("new", "NEW", p) {}
};

class GreaterThan : Terminal {
public:
  GreaterThan(NonTerminal *p) : Terminal(">", "GREATER_THAN", p) {}
};

class LessThan : Terminal {
public:
  LessThan(NonTerminal *p) : Terminal("<", "LESS_THAN", p) {}
};

class LessOrEquals : Terminal {
public:
  LessOrEquals(NonTerminal *p) : Terminal("<=", "LESS_OR_EQUALS", p) {}
};

class GreaterOrEquals : Terminal {
public:
  GreaterOrEquals(NonTerminal *p) : Terminal(">=", "GREATER_OR_EQUALS", p) {}
};

class Equals : Terminal {
public:
  Equals(NonTerminal *p) : Terminal("==", "EQUALS", p) {}
};

class Different : Terminal {
public:
  Different(NonTerminal *p) : Terminal("!=", "DIFFERENT", p) {}
};

class Minus : Terminal {
public:
  Minus(NonTerminal *p) : Terminal("-", "MINUS", p) {}
};

class Positive : Terminal {
public:
  Positive(NonTerminal *p) : Terminal("+", "POSITIVE", p) {}
};

class Times : Terminal {
public:
  Times(NonTerminal *p) : Terminal("*", "TIMES", p) {}
};

class Divide : Terminal {
public:
  Divide(NonTerminal *p) : Terminal("/", "DIVIDE", p) {}
};

class Remainder : Terminal {
public:
  Remainder(NonTerminal *p) : Terminal("%", "REMAINDER", p) {}
};

class IntConstant : Terminal {
public:
  IntConstant(std::string lexicalValue, NonTerminal *p) : Terminal(lexicalValue, "INT_CONSTANT", p) {}
};

class FloatConstant : Terminal {
public:
  FloatConstant(std::string lexicalValue, NonTerminal *p) : Terminal(lexicalValue, "FLOAT_CONSTANT", p) {}
};

class StringConstant : Terminal {
public:
  StringConstant(std::string lexicalValue, NonTerminal *p) : Terminal(lexicalValue, "STRING_CONSTANT", p) {}
};

class Null : Terminal {
public:
  Null(NonTerminal *p) : Terminal("null", "NULL", p) {}
};

class PROGRAM : NonTerminal {
public:
  PROGRAM(NonTerminal *parent) : NonTerminal("PROGRAM", parent) {}
};

class STATEMENT : NonTerminal {
public:
  STATEMENT(NonTerminal *parent) : NonTerminal("STATEMENT", parent) {}
};

class FUNCLIST : NonTerminal {
public:
  FUNCLIST(NonTerminal *parent) : NonTerminal("FUNCLIST", parent) {}
};

class FUNCDEF : NonTerminal {
public:
  FUNCDEF(NonTerminal *parent) : NonTerminal("FUNCDEF", parent) {}
};

class TYPE : NonTerminal {
public:
  TYPE(NonTerminal *parent) : NonTerminal("TYPE", parent) {}
};

class PARAMLIST : NonTerminal {
public:
  PARAMLIST(NonTerminal *parent) : NonTerminal("PARAMLIST", parent) {}
};

class VARDECL : NonTerminal {
public:
  VARDECL(NonTerminal *parent) : NonTerminal("VARDECL", parent) {}
};

class ARRAYVARDECL : NonTerminal {
public:
  ARRAYVARDECL(NonTerminal *parent) : NonTerminal("ARRAYVARDECL", parent) {}
};

class ATRIBSTAT : NonTerminal {
public:
  ATRIBSTAT(NonTerminal *parent) : NonTerminal("ATRIBSTAT", parent) {}
};

class FUNCCALL : NonTerminal {
public:
  FUNCCALL(NonTerminal *parent) : NonTerminal("FUNCCALL", parent) {}
};

class PARAMLISTCALL : NonTerminal {
public:
  PARAMLISTCALL(NonTerminal *parent) : NonTerminal("PARAMLISTCALL", parent) {}
};


class PARAMLISTCALLA : NonTerminal {
public:
  PARAMLISTCALLA(NonTerminal *parent) : NonTerminal("PARAMLISTCALL'", parent) {}
};

class PRINTSTAT : NonTerminal {
public:
  PRINTSTAT(NonTerminal *parent) : NonTerminal("PRINTSTAT", parent) {}
};

class READSTAT : NonTerminal {
public:
  READSTAT(NonTerminal *parent) : NonTerminal("READSTAT", parent) {}
};

class RETURNSTAT : NonTerminal {
public:
  RETURNSTAT(NonTerminal *parent) : NonTerminal("RETURNSTAT", parent) {}
};

class IFSTAT : NonTerminal {
public:
  IFSTAT(NonTerminal *parent) : NonTerminal("IFSTAT", parent) {}
};

class ELSESTAT : NonTerminal {
public:
  ELSESTAT(NonTerminal *parent) : NonTerminal("ELSESTAT", parent) {}
};

class FORSTAT : NonTerminal {
public:
  FORSTAT(NonTerminal *parent) : NonTerminal("FORSTAT", parent) {}
};

class STATELIST : NonTerminal {
public:
  STATELIST(NonTerminal *parent) : NonTerminal("STATELIST", parent) {}
};

class STATELISTA : NonTerminal {
public:
  STATELISTA(NonTerminal *parent) : NonTerminal("STATELIST'", parent) {}
};

class ALLOCEXPRESION : NonTerminal {
public:
  ALLOCEXPRESION(NonTerminal *parent) : NonTerminal("ALLOCEXPRESION", parent) {}
};

class NUMLIST : NonTerminal {
public:
  NUMLIST(NonTerminal *parent) : NonTerminal("NUM_LIST", parent) {}
};

class NUMLISTA : NonTerminal {
public:
  NUMLISTA(NonTerminal *parent) : NonTerminal("NUM_LIST'", parent) {}
};

class RELOP : NonTerminal {
public:
  RELOP(NonTerminal *parent) : NonTerminal("RELOP", parent) {}
};

class EXPRESSION : NonTerminal {
public:
  EXPRESSION(NonTerminal *parent) : NonTerminal("EXPRESSION", parent) {}
};

class EXPRESSIONA : NonTerminal {
public:
  EXPRESSIONA(NonTerminal *parent) : NonTerminal("EXPRESSION'", parent) {}
};

class SIGNAL : NonTerminal {
public:
  SIGNAL(NonTerminal *parent) : NonTerminal("SIGNAL", parent) {}
};

class NUMEXPRESSION : NonTerminal {
public:
  NUMEXPRESSION(NonTerminal *parent) : NonTerminal("NUMEXPRESSION", parent) {}
};

class NUMEXPRESSIONA : NonTerminal {
public:
  NUMEXPRESSIONA(NonTerminal *parent) : NonTerminal("NUMEXPRESSION'", parent) {}
};

class TERMREC : NonTerminal {
public:
  TERMREC(NonTerminal *parent) : NonTerminal("TERM_REC", parent) {}
};

class TERMRECA : NonTerminal {
public:
  TERMRECA(NonTerminal *parent) : NonTerminal("TERM_REC'", parent) {}
};

class OPERATOR : NonTerminal {
public:
  OPERATOR(NonTerminal *parent) : NonTerminal("OPERATOR", parent) {}
};

class TERM : NonTerminal {
public:
  TERM(NonTerminal *parent) : NonTerminal("TERM", parent) {}
};

class UNARYEXPRREC : NonTerminal {
public:
  UNARYEXPRREC(NonTerminal *parent) : NonTerminal("UNARYEXPR_REC", parent) {}
};

class UNARYEXPRRECA : NonTerminal {
public:
  UNARYEXPRRECA(NonTerminal *parent) : NonTerminal("UNARYEXPR_REC'", parent) {}
};

class UNARYEXPR : NonTerminal {
public:
  UNARYEXPR(NonTerminal *parent) : NonTerminal("UNARYEXPR", parent) {}
};

class FACTOR : NonTerminal {
public:
  FACTOR(NonTerminal *parent) : NonTerminal("FACTOR", parent) {}
};

class LVALUE : NonTerminal {
public:
  LVALUE(NonTerminal *parent) : NonTerminal("LVALUE", parent) {}
};

class NUMEXPRESSIONREC : NonTerminal {
public:
  NUMEXPRESSIONREC(NonTerminal *parent) : NonTerminal("NUMEXPRESSION_REC", parent) {}
};

class NUMEXPRESSIONRECA : NonTerminal {
public:
  NUMEXPRESSIONRECA(NonTerminal *parent) : NonTerminal("NUMEXPRESSION_REC'", parent) {}
};

class SyntaxAnalyzer
{
private:
  std::vector<std::string> stack;
  std::vector<Production> productions;
  std::unordered_map<std::string, std::unordered_map<std::string, int>> parseTable;
  LexicalAnalyzer *lexicalAnalyzer;

public:
  SyntaxAnalyzer(LexicalAnalyzer *la);

  void parse();
};

#endif