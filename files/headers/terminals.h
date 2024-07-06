#ifndef TERMINALS_ANALYZER_H
#define TERMINALS_ANALYZER_H

#include <parser.h>

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

class DollarSign : public Item {
public:
  DollarSign() : Item() {
    terminal = new Terminal("$", "$", NULL);
    type = TERMINAL;
  }
};


#endif
