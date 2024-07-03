#ifndef PARSER_H
#define PARSER_H

#include "token.h"

#include <unordered_map>
#include <string>
#include <vector>

class SemanticAction  {
public:
  std::string name;

  std::string value() {
    return name;
  };
};

class NonTerminal {
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

enum ItemType {
  NON_TERMINAL,
  TERMINAL,
  SEMANTIC_ACTION,
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

class Epsilon : public Item {
public:
  Epsilon(NonTerminal *p)  {
    terminal = new Terminal("&", "EPSILON", p);
    type = TERMINAL;
  }
};

class Def : public Item {
public:
  Def(NonTerminal *p) {
    terminal = new Terminal("def", "DEF", p);
    type = TERMINAL;
  }
};

class Ident : public Item {
public:
  Ident(std::string lexicalValue, NonTerminal *p) {
    terminal = new Terminal(lexicalValue, "IDENT", p);
    type = TERMINAL;
  }
};

class OpenParentheses : public Item {
public:
  OpenParentheses(NonTerminal *p) {
    terminal = new Terminal("(", "OPEN_PARENTHESES", p);
    type = TERMINAL;
  }
};

class CloseParentheses : public Item {
public:
  CloseParentheses(NonTerminal *p) {
    terminal = new Terminal(")", "CLOSE_PARENTHESES", p);
    type = TERMINAL;
  }
};

class OpenBrackets : public Item {
public:
  OpenBrackets(NonTerminal *p) {
    terminal = new Terminal("{", "OPEN_BRACKETS", p);
    type = TERMINAL;
  }
};

class CloseBrackets : public Item {
public:
  CloseBrackets(NonTerminal *p) {
    terminal = new Terminal("}", "CLOSE_BRACKETS", p);
    type = TERMINAL;
  }
};

class Int : public Item {
public:
  Int(NonTerminal *p) {
    terminal = new Terminal("int", "INT", p);
    type = TERMINAL;
  }
};

class Float : public Item {
public:
  Float(NonTerminal *p) {
    terminal = new Terminal("float", "FLOAT", p);
    type = TERMINAL;
  }
};

class String : public Item {
public:
  String(NonTerminal *p) {
    terminal = new Terminal("string", "STRING", p);
    type = TERMINAL;
  }
};

class Comma : public Item {
public:
  Comma(NonTerminal *p) {
    terminal = new Terminal(",", "COMMA", p);
    type = TERMINAL;
  }
};

class Semicolon : public Item {
public:
  Semicolon(NonTerminal *p) {
    terminal = new Terminal(";", "SEMICOLON", p);
    type = TERMINAL;
  }
};

class Break : public Item {
public:
  Break(NonTerminal *p) {
    terminal = new Terminal("break", "BREAK", p);
    type = TERMINAL;
  }
};

class OpenSquareBrackets : public Item {
public:
  OpenSquareBrackets(NonTerminal *p) {
    terminal = new Terminal("[", "OPEN_SQUARE_BRACKETS", p);
    type = TERMINAL;
  }
};

class CloseSquareBrackets : public Item {
public:
  CloseSquareBrackets(NonTerminal *p) {
    terminal = new Terminal("]", "CLOSE_SQUARE_BRACKETS", p);
    type = TERMINAL;
  }
};

class Equal : public Item {
public:
  Equal(NonTerminal *p) {
    terminal = new Terminal("=", "EQUAL", p);
    type = TERMINAL;
  }
};

class Call : public Item {
public:
  Call(NonTerminal *p) {
    terminal = new Terminal("call", "CALL", p);
    type = TERMINAL;
  }
};

class Print : public Item {
public:
  Print(NonTerminal *p) {
    terminal = new Terminal("print", "PRINT", p);
    type = TERMINAL;
  }
};

class Read : public Item {
public:
  Read(NonTerminal *p) {
    terminal = new Terminal("read", "READ", p);
    type = TERMINAL;
  }
};

class Return : public Item {
public:
  Return (NonTerminal *p) {
    terminal = new Terminal("return", "RETURN", p);
    type = TERMINAL;
  }
};

class If : public Item {
public:
  If(NonTerminal *p) {
    terminal = new Terminal("if", "IF", p);
    type = TERMINAL;
  }
};

class Else : public Item {
public:
  Else(NonTerminal *p) {
    terminal = new Terminal("else", "ELSE", p);
    type = TERMINAL;
  }
};

class For : public Item {
public:
  For(NonTerminal *p) {
    terminal = new Terminal("for", "FOR", p);
    type = TERMINAL;
  }
};

class New : public Item {
public:
  New(NonTerminal *p) {
    terminal = new Terminal("new", "NEW", p);
    type = TERMINAL;
  }
};

class GreaterThan : public Item {
public:
  GreaterThan(NonTerminal *p) {
    terminal = new Terminal(">", "GREATER_THAN", p);
    type = TERMINAL;
  }
};

class LessThan : public Item {
public:
  LessThan(NonTerminal *p) {
    terminal = new Terminal("<", "LESS_THAN", p);
    type = TERMINAL;
  }
};

class LessOrEquals : public Item {
public:
  LessOrEquals(NonTerminal *p) {
    terminal = new Terminal("<=", "LESS_OR_EQUALS", p);
    type = TERMINAL;
  }
};

class GreaterOrEquals : public Item {
public:
  GreaterOrEquals(NonTerminal *p) {
    terminal = new Terminal(">=", "GREATER_OR_EQUALS", p);
    type = TERMINAL;
  }
};

class Equals : public Item {
public:
  Equals(NonTerminal *p) {
    terminal = new Terminal("==", "EQUALS", p);
    type = TERMINAL;
  }
};

class Different : public Item {
public:
  Different(NonTerminal *p) {
    terminal = new Terminal("!=", "DIFFERENT", p);
    type = TERMINAL;
  }
};

class Minus : public Item {
public:
  Minus(NonTerminal *p) {
    terminal = new Terminal("-", "MINUS", p);
    type = TERMINAL;
  }
};

class Positive : public Item {
public:
  Positive(NonTerminal *p) {
    terminal = new Terminal("+", "POSITIVE", p);
    type = TERMINAL;
  }
};

class Times : public Item {
public:
  Times(NonTerminal *p) {
    terminal = new Terminal("*", "TIMES", p);
    type = TERMINAL;
  }
};

class Divide : public Item {
public:
  Divide(NonTerminal *p) {
    terminal = new Terminal("/", "DIVIDE", p);
    type = TERMINAL;
  }
};

class Remainder : public Item {
public:
  Remainder(NonTerminal *p) {
    terminal = new Terminal("%", "REMAINDER", p);
    type = TERMINAL;
  }
};

class IntConstant : public Item {
public:
  IntConstant(std::string lexicalValue, NonTerminal *p) {
    terminal = new Terminal(lexicalValue, "INT_CONSTANT", p);
    type = TERMINAL;
  }
};

class FloatConstant : public Item {
public:
  FloatConstant(std::string lexicalValue, NonTerminal *p) {
    terminal = new Terminal(lexicalValue, "FLOAT_CONSTANT", p);
    type = TERMINAL;
  }
};

class StringConstant : public Item {
public:
  StringConstant(std::string lexicalValue, NonTerminal *p) {
    terminal = new Terminal(lexicalValue, "STRING_CONSTANT", p);
    type = TERMINAL;
  }
};

class Null : public Item {
public:
  Null(NonTerminal *p) {
    terminal = new Terminal("null", "NULL", p);
    type = TERMINAL;
  }
};

class Program : public Item {
public:
  Program(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PROGRAM", parent);
    type = NON_TERMINAL;
  }
};

class Statement : public Item {
public:
  Statement(NonTerminal *parent) {
    nonTerminal = new NonTerminal("STATEMENT", parent);
    type = NON_TERMINAL;
  }
};

class Funclist : public Item {
public:
  Funclist(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FUNCLIST", parent);
    type = NON_TERMINAL;
  }
};

class Funcdef : public Item {
public:
  Funcdef(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FUNCDEF", parent);
    type = NON_TERMINAL;
  }
};

class Type : public Item {
public:
  Type(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TYPE", parent);
    type = NON_TERMINAL;
  }
};

class Paramlist : public Item {
public:
  Paramlist(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PARAMLIST", parent);
    type = NON_TERMINAL;
  }
};

class Vardecl : public Item {
public:
  Vardecl(NonTerminal *parent) {
    nonTerminal = new NonTerminal("VARDECL", parent);
    type = NON_TERMINAL;
  }
};

class Arrayvardecl : public Item {
public:
  Arrayvardecl(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ARRAYVARDECL", parent);
    type = NON_TERMINAL;
  }
};

class Atribstat : public Item {
public:
  Atribstat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ATRIBSTAT", parent);
    type = NON_TERMINAL;
  }
};

class Atribstata : public Item {
public:
  Atribstata(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ATRIBSTAT'", parent);
    type = NON_TERMINAL;
  }
};

class Funccall : public Item {
public:
  Funccall(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FUNCCALL", parent);
    type = NON_TERMINAL;
  }
};

class Paramlistcall : public Item {
public:
  Paramlistcall(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PARAMLISTCALL", parent);
    type = NON_TERMINAL;
  }
};


class Paramlistcalla : public Item {
public:
  Paramlistcalla(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PARAMLISTCALL'", parent);
    type = NON_TERMINAL;
  }
};

class Printstat : public Item {
public:
  Printstat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PRINTSTAT", parent);
    type = NON_TERMINAL;
  }
};

class ReadStat : public Item {
public:
  ReadStat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("READSTAT", parent);
    type = NON_TERMINAL;
  }
};

class ReturnStat : public Item {
public:
  ReturnStat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("RETURNSTAT", parent);
    type = NON_TERMINAL;
  }
};

class Ifstat : public Item {
public:
  Ifstat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("IFSTAT", parent);
    type = NON_TERMINAL;
  }
};

class Elsestat : public Item {
public:
  Elsestat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ELSESTAT", parent);
    type = NON_TERMINAL;
  }
};

class Forstat : public Item {
public:
  Forstat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FORSTAT", parent);
    type = NON_TERMINAL;
  }
};

class Statelist : public Item {
public:
  Statelist(NonTerminal *parent) {
    nonTerminal = new NonTerminal("STATELIST", parent);
    type = NON_TERMINAL;
  }
};

class Statelista : public Item {
public:
  Statelista(NonTerminal *parent) {
    nonTerminal = new NonTerminal("STATELIST'", parent);
    type = NON_TERMINAL;
  }
};

class Allocexpression : public Item {
public:
  Allocexpression(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ALLOCEXPRESION", parent);
    type = NON_TERMINAL;
  }
};

class Numlist : public Item {
public:
  Numlist(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUM_LIST", parent);
    type = NON_TERMINAL;
  }
};

class Numlista : public Item {
public:
  Numlista(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUM_LIST'", parent);
    type = NON_TERMINAL;
  }
};

class Relop : public Item {
public:
  Relop(NonTerminal *parent) {
    nonTerminal = new NonTerminal("RELOP", parent);
    type = NON_TERMINAL;
  }
};

class Expression : public Item {
public:
  Expression(NonTerminal *parent) {
    nonTerminal = new NonTerminal("EXPRESSION", parent);
    type = NON_TERMINAL;
  }
};

class Expressiona : public Item {
public:
  Expressiona(NonTerminal *parent) {
    nonTerminal = new NonTerminal("EXPRESSION'", parent);
    type = NON_TERMINAL;
  }
};

class Signal : public Item {
public:
  Signal(NonTerminal *parent) {
    nonTerminal = new NonTerminal("SIGNAL", parent);
    type = NON_TERMINAL;
  }
};

class Numexpression : public Item {
public:
  Numexpression(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUMEXPRESSION", parent);
    type = NON_TERMINAL;
  }
};

class Numexpressiona : public Item {
public:
  Numexpressiona(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUMEXPRESSION'", parent);
    type = NON_TERMINAL;
  }
};

class Termrec : public Item {
public:
  Termrec(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TERM_REC", parent);
    type = NON_TERMINAL;
  }
};

class Termreca : public Item {
public:
  Termreca(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TERM_REC'", parent);
    type = NON_TERMINAL;
  }
};

class Operator : public Item {
public:
  Operator(NonTerminal *parent) {
    nonTerminal = new NonTerminal("OPERATOR", parent);
    type = NON_TERMINAL;
  }
};

class Term : public Item {
public:
  Term(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TERM", parent);
    type = NON_TERMINAL;
  }
};

class Terma : public Item {
public:
  Terma(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TERM'", parent);
    type = NON_TERMINAL;
  }
};


class Unaryexprrec : public Item {
public:
  Unaryexprrec(NonTerminal *parent) {
    nonTerminal = new NonTerminal("UNARYEXPR_REC", parent);
    type = NON_TERMINAL;
  }
};

class Unaryexprreca : public Item {
public:
  Unaryexprreca(NonTerminal *parent) {
    nonTerminal = new NonTerminal("UNARYEXPR_REC'", parent);
    type = NON_TERMINAL;
  }
};

class Unaryexpr : public Item {
public:
  Unaryexpr(NonTerminal *parent) {
    nonTerminal = new NonTerminal("UNARYEXPR", parent);
    type = NON_TERMINAL;
  }
};

class Factor : public Item {
public:
  Factor(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FACTOR", parent);
    type = NON_TERMINAL;
  }
};

class Lvalue : public Item {
public:
  Lvalue(NonTerminal *parent) {
    nonTerminal = new NonTerminal("LVALUE", parent);
    type = NON_TERMINAL;
  }
};

class Lvaluea : public Item {
public:
  Lvaluea(NonTerminal *parent) {
    nonTerminal = new NonTerminal("LVALUE'", parent);
    type = NON_TERMINAL;
  }
};

class Numexpressionrec : public Item {
public:
  Numexpressionrec(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUMEXPRESSION_REC", parent);
    type = NON_TERMINAL;
  }
};

class Numexpressionreca : public Item {
public:
  Numexpressionreca(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUMEXPRESSION_REC'", parent);
    type = NON_TERMINAL;
  }
};

class DollarSign : public Item {
public:
  DollarSign() : Item() {
    nonTerminal = new NonTerminal("$", NULL);
    type = NON_TERMINAL;
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

    public:
        Parser();

        void parse(std::vector<Token*> tokens);

        std::vector<Item> generateNewTokens(int production, NonTerminal *parent);
};

#endif